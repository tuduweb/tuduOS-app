/*
 * Copyright (c) 2006-2019, ZX-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-12     ChenYong  first version
 */

#ifndef __SYSINFO_H__
#define __SYSINFO_H__

#include <zxthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYS_VER_LEN           6

#define IOC_SYSINFO          (0x01)
#define IOC_LWPINFO          (0x02)
#define IOC_THREADINFO       (0x03)

struct sysinfo
{
    char kernel_ver[SYS_VER_LEN];       /* kernel version */
    char hw_ver[SYS_VER_LEN];           /* hardware version */
    zx_uint32_t totle_ram;
    zx_uint32_t used_ram;
    zx_uint32_t max_used_ram;
    zx_uint32_t totle_rom;
    zx_uint32_t used_rom;

    int ram_usage;                     /* sysytem ram usage */
    int rom_usage;                     /* system rom usgae  */
    int cpu_usage;                     /* system cpu usage */
    zx_uint8_t procs;                  /* the number of system processes */
};

struct lwpinfo
{
    char name[ZX_NAME_MAX];           /* lwp process name */
    int cpu_usage;                    /* lwp cpu usage */
    zx_uint8_t threads;               /* the number of lwp threads */
};

struct threadinfo
{
    struct zx_thread *thread;         /* thread object */
    zx_uint32_t kstack_size;          /* thread kernel stack totle size */
    zx_uint32_t kstack_max_used;      /* the maximum number of kernel stacks used */
    zx_uint32_t ustack_size;          /* thread user stack totle size */
    zx_uint32_t ustack_max_uesd;      /* the maximum number of user stacks used  */

    int kstack_usage;                 /* thread kernel stack usage */
    int ustack_usage;                 /* thread user stack stack usage */
    int cpu_usage;                    /* thread cpu usage */
};

#ifdef __cplusplus
}
#endif

#endif /* __SYSINFO_H__ */
