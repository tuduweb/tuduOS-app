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
    return (rt_thread_t) syscall(0x60, name, entry, parameter, user_stack, user_stack_size, priority);//tick
}


rt_err_t rt_thread_startup(rt_thread_t thread)
{
    return (rt_err_t) syscall(0x61, thread);
}
