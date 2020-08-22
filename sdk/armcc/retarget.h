#include "rtdef.h"


extern int syscall(int number, ...);

extern rt_thread_t rt_thread_create(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick);

extern rt_err_t rt_thread_startup(rt_thread_t thread);

extern rt_err_t rt_thread_mdelay(rt_int32_t ms);

extern rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag);
extern rt_err_t rt_mb_delete(rt_mailbox_t mb);
extern rt_err_t rt_mb_send(rt_mailbox_t mb, rt_ubase_t value);
extern rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout);


