/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <stdint.h>
#include <assert.h>
#include "zynq7000/gic.h"
#include "zynq7000/cp15.h"
#include <stdio.h>
#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define ARM_GIC_MAX_NR 1
#define ARM_GIC_NR_IRQS 94
struct arm_gic
{
    uint32_t offset;

    uint32_t dist_hw_base;
    uint32_t cpu_hw_base;
};
static struct arm_gic _gic_table[ARM_GIC_MAX_NR];

#define GIC_CPU_CTRL(hw_base)               __REG32((hw_base) + 0x00)
#define GIC_CPU_PRIMASK(hw_base)            __REG32((hw_base) + 0x04)
#define GIC_CPU_BINPOINT(hw_base)           __REG32((hw_base) + 0x08)
#define GIC_CPU_INTACK(hw_base)             __REG32((hw_base) + 0x0c)
#define GIC_CPU_EOI(hw_base)                __REG32((hw_base) + 0x10)
#define GIC_CPU_RUNNINGPRI(hw_base)         __REG32((hw_base) + 0x14)
#define GIC_CPU_HIGHPRI(hw_base)            __REG32((hw_base) + 0x18)

#define GIC_DIST_CTRL(hw_base)              __REG32((hw_base) + 0x000)
#define GIC_DIST_TYPE(hw_base)               __REG32((hw_base) + 0x004)
#define GIC_DIST_IGROUP(hw_base, n)         __REG32((hw_base) + 0x080 + (n/32) * 4)
#define GIC_DIST_ENABLE_SET(hw_base, n)     __REG32((hw_base) + 0x100 + (n/32) * 4)
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x180 + (n/32) * 4)
#define GIC_DIST_PENDING_SET(hw_base, n)    __REG32((hw_base) + 0x200)
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  __REG32((hw_base) + 0x280 + (n/32) * 4)
#define GIC_DIST_ACTIVE_BIT(hw_base)        __REG32((hw_base) + 0x300)
#define GIC_DIST_PRI(hw_base, n)            __REG32((hw_base) + 0x400 +  (n/4) * 4)
#define GIC_DIST_TARGET(hw_base, n)         __REG32((hw_base) + 0x800 +  (n/4) * 4)
#define GIC_DIST_CONFIG(hw_base, n)         __REG32((hw_base) + 0xc00 + (n/16) * 4)
#define GIC_DIST_SOFTINT(hw_base)           __REG32((hw_base) + 0xf00)
#define GIC_DIST_CPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf10 + (n/4) * 4)
#define GIC_DIST_ICPIDR2(hw_base)           __REG32((hw_base) + 0xfe8)

static unsigned int _gic_max_irq;

int arm_gic_get_active_irq(uint32_t index)
{
    int irq;

    assert(index < ARM_GIC_MAX_NR);

    irq = GIC_CPU_INTACK(_gic_table[index].cpu_hw_base);
    irq += _gic_table[index].offset;
    return irq;
}

void arm_gic_ack(uint32_t index, int irq)
{
    uint32_t mask = 1 << (irq % 32);

    assert(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    assert(irq >= 0);

    GIC_DIST_PENDING_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    GIC_CPU_EOI(_gic_table[index].cpu_hw_base) = irq;
}

void arm_gic_mask(uint32_t index, int irq)
{
    uint32_t mask = 1 << (irq % 32);

    assert(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    assert(irq >= 0);

    GIC_DIST_ENABLE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}
//arm_gic_set_cpu(0, vector, 1 << rt_cpu_get_smp_id());
void arm_gic_set_cpu(uint32_t index, int irq, unsigned int cpumask)
{
    uint32_t old_tgt;

    assert(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    assert(irq >= 0);

    old_tgt = GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq);

    old_tgt &= ~(0x0FFUL << ((irq % 4)*8));
    old_tgt |=   cpumask << ((irq % 4)*8);

    GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) = old_tgt;
}

void arm_gic_umask(uint32_t index, int irq)
{
    uint32_t mask = 1 << (irq % 32);

    assert(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    assert(irq >= 0);

    GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, irq) = mask;
}

void arm_gic_dump_type(uint32_t index)
{
    unsigned int gic_type;

    gic_type = GIC_DIST_TYPE(_gic_table[index].dist_hw_base);
    printf("GICv%ld on %p, max IRQs: %d, %s security extension(%08x)\n",
               (GIC_DIST_ICPIDR2(_gic_table[index].dist_hw_base) >> 4) & 0xf,
               _gic_table[index].dist_hw_base,
               _gic_max_irq,
               gic_type & (1 << 10) ? "has" : "no",
               gic_type);
}
extern int cpu_get_smp_id();

int arm_gic_dist_init(uint32_t index, uint32_t dist_base, int irq_start)
{
    unsigned int gic_type, i;
    uint32_t cpuid = cpu_get_smp_id();
    uint32_t cpumask = (cpuid + 1) << 0;

    assert(index < ARM_GIC_MAX_NR);

    _gic_table[index].dist_hw_base = dist_base;
    _gic_table[index].offset = irq_start;

    /* Find out how many interrupts are supported. */
    gic_type = GIC_DIST_TYPE(dist_base);
    _gic_max_irq = ((gic_type & 0x1f) + 1) * 32;

    /*
     * The GIC only supports up to 1020 interrupt sources.
     * Limit this to either the architected maximum, or the
     * platform maximum.
     */
    if (_gic_max_irq > 1020)
        _gic_max_irq = 1020;
    if (_gic_max_irq > ARM_GIC_NR_IRQS)
        _gic_max_irq = ARM_GIC_NR_IRQS;

    cpumask |= cpumask << 8;
    cpumask |= cpumask << 16;

    GIC_DIST_CTRL(dist_base) = 0x0;

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32; i < _gic_max_irq; i += 16)
        GIC_DIST_CONFIG(dist_base, i) = 0x0;

    /* Set all global interrupts to this CPU only. */
    for (i = 32; i < _gic_max_irq; i += 4)
        GIC_DIST_TARGET(dist_base, i) = cpumask;

    /* Set priority on all interrupts. */
    for (i = 0; i < _gic_max_irq; i += 4)
        GIC_DIST_PRI(dist_base, i) = 0xa0a0a0a0;

    /* Disable all interrupts. */
    for (i = 0; i < _gic_max_irq; i += 32)
        GIC_DIST_ENABLE_CLEAR(dist_base, i) = 0xffffffff;

    /* Set the FIQEn bit, signal FIQ for IGROUP0. */
    GIC_DIST_CTRL(dist_base) = 0x01;

    return 0;
}

int arm_gic_cpu_init(uint32_t index, uint32_t cpu_base)
{
    assert(index < ARM_GIC_MAX_NR);

    _gic_table[index].cpu_hw_base = cpu_base;

    GIC_CPU_PRIMASK(cpu_base) = 0xf0;
    /* Enable CPU interrupt */
    GIC_CPU_CTRL(cpu_base) = 0x01;

    return 0;
}

void arm_gic_set_group(uint32_t index, int vector, int group)
{
    /* As for GICv2, there are only group0 and group1. */
    assert(group <= 1);
    assert(vector < _gic_max_irq);

    if (group == 0)
    {
        GIC_DIST_IGROUP(_gic_table[index].dist_hw_base,
                        vector) &= ~(1 << (vector % 32));
    }
    else if (group == 1)
    {
        GIC_DIST_IGROUP(_gic_table[index].dist_hw_base,
                        vector) |=  (1 << (vector % 32));
    }
}

void arm_gic_trigger(uint32_t index, int target_cpu, int irq)
{
    unsigned int reg;

    assert(irq <= 15);
    assert(target_cpu <= 255);

    reg = (target_cpu << 16) | irq;
    GIC_DIST_SOFTINT(_gic_table[index].dist_hw_base) = reg;
}

void arm_gic_clear_sgi(uint32_t index, int target_cpu, int irq)
{
    assert(irq <= 15);
    assert(target_cpu <= 255);

    GIC_DIST_CPENDSGI(_gic_table[index].dist_hw_base, irq) = target_cpu << (irq % 4);
}
