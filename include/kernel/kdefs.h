#pragma once

#include <stdint.h>
#include <stddef.h>
#include <config.h>

#ifndef CONFIG_ZYNQ7000_CPUS
    #define nBrOfCPUs (2)
#else
    #define nBrOfCPUs CONFIG_ZYNQ7000_CPUS
#endif

#define ALIGN(n) __attribute__((aligned(n)))
#define ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

typedef uint32_t k_err_t;

#define KERNEL_EOK                          (0)               /**< There is no error */
#define KERNEL_ERROR                        (-1)               /**< A generic error happens */
#define KERNEL_ETIMEOUT                     (-2)               /**< Timed out */
#define KERNEL_EFULL                        (-3)               /**< The resource is full */
#define KERNEL_EEMPTY                       (-4)               /**< The resource is empty */
#define KERNEL_ENOMEM                       (-5)               /**< No memory */
#define KERNEL_ENOSYS                       (-6)               /**< No system */
#define KERNEL_EBUSY                        (-7)               /**< Busy */
#define KERNEL_EIO                          (-8)               /**< IO error */
#define KERNEL_EINTR                        (-9)               /**< Interrupted system call */
#define KERNEL_EINVAL                       (-10)              /**< Invalid argument */

/* 已知一个结构体里面的成员的地址，反推出该结构体的首地址 */
#define k_container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))
			
