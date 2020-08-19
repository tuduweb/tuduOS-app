#include "bin_mem.h"
#include "tlsf.h"

extern unsigned int Image$$data$$RW$$Length;
tlsf_t tlsf;
/**
 * 初始化App的堆
 */
void app_heap_init(void *begin_addr,void *end_addr)
{
    //
    rt_uint32_t heap_size = (rt_uint32_t)end_addr - (rt_uint32_t)begin_addr;
    tlsf = tlsf_create_with_pool((void *)((rt_uint32_t)begin_addr + 0x100), heap_size - 0x100);
}

void *malloc(rt_size_t size)
{
    return tlsf_malloc(tlsf, size);
}

