#ifndef __BIN_SDK_MEMORY__
#define __BIN_SDK_MEMORY__

#include "rtdef.h"



extern void app_heap_init(void *begin_addr,void *end_addr);

extern void *malloc(rt_size_t size);

#endif
