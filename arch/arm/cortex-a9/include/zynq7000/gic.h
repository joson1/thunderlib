/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#ifndef __GIC_H__
#define __GIC_H__

int arm_gic_dist_init(uint32_t index, uint32_t dist_base, int irq_start);
int arm_gic_cpu_init(uint32_t index, uint32_t cpu_base);

void arm_gic_mask(uint32_t index, int irq);
void arm_gic_umask(uint32_t index, int irq);
void arm_gic_set_cpu(uint32_t index, int irq, unsigned int cpumask);
void arm_gic_set_group(uint32_t index, int vector, int group);

int arm_gic_get_active_irq(uint32_t index);
void arm_gic_ack(uint32_t index, int irq);

void arm_gic_trigger(uint32_t index, int target_cpu, int irq);
void arm_gic_clear_sgi(uint32_t index, int target_cpu, int irq);

void arm_gic_dump_type(uint32_t index);

#endif

