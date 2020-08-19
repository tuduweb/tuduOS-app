#include "rtdef.h"


extern int syscall(int number, ...);

rt_thread_t rt_thread_create(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick);

rt_err_t rt_thread_startup(rt_thread_t thread);
