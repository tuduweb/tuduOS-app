#include "stdio.h"
#include "retarget.h"
#include "bin_mem.h"

#pragma import(__use_no_semihosting_swi)
#pragma import(__use_no_semihosting)

void _sys_exit(int code) { 
    syscall(0x01,code);
}

struct __FILE  { 
    int handle; 
    /* Whatever you require here. If the only file you are using is */ 
    /* standard output using printf() for debugging, no file handling */ 
    /* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;

void _ttywrch(int ch)
{
    ch = ch;
}

int fputc(int ch, FILE *f){      
    return 0;
}

/**
 * 注意参数不同于os
*/
rt_thread_t rt_thread_create(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t user_stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick)
{
    void *user_stack;
    user_stack = malloc(user_stack_size);
    if(user_stack == RT_NULL)
    {
        return RT_NULL;
    }
    return (rt_thread_t) syscall(0x60, name, entry, parameter, user_stack, user_stack_size, priority);//tick
}


rt_err_t rt_thread_startup(rt_thread_t thread)
{
    return (rt_err_t) syscall(0x61, thread);
}

rt_err_t rt_thread_mdelay(rt_int32_t ms)
{
    return (rt_err_t) syscall(0x62, ms);
}

rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    return (rt_mailbox_t) syscall(0x63, name, size, flag);
}
rt_err_t rt_mb_delete(rt_mailbox_t mb)
{
    return (rt_err_t) syscall(0x64, mb);
}
rt_err_t rt_mb_send(rt_mailbox_t mb, rt_ubase_t value)
{
    return (rt_err_t) syscall(0x65, mb, value);
}
rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    return (rt_err_t) syscall(0x66, mb, value, timeout);
}


