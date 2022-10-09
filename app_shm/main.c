#include "retarget.h"
#include "stdint.h"
#include "bin_mem.h"

#include <stdio.h>

#define HEAP_SIZE  0x2000
#define STACK_SIZE 0x200
__attribute__((used)) __attribute__((section("HEAP"))) __attribute__((zero_init)) static char app_heap[HEAP_SIZE];
__attribute__((used)) __attribute__((section("STACK"))) __attribute__((zero_init))  static char app_stack[STACK_SIZE];

rt_mailbox_t mb;

static void lwt_thread_entry(void* parameter)
{
	rt_uint32_t shmAddr = (rt_uint32_t)parameter;

	rt_err_t res = lwt_shm_retain((void *)shmAddr);

	if(res == 0) {
		rt_kprintf("inlwt print: %s\r\n", (char *)shmAddr);
	}else{
		rt_kprintf("inlwt err: %d\r\n", res);
	}

	for(int i = 0; i < 2; ++i) {
		rt_thread_mdelay(500);
		rt_kprintf("inlwt tick %d\r\n", i);
	}

	lwt_shm_free((void *)shmAddr);

	return;

}

rt_thread_t thread = 0;




int main(int argc, const char **argv, const char **envp) {
	
	app_heap_init(app_heap, app_heap + HEAP_SIZE);

	rt_uint32_t addr = (rt_uint32_t)lwt_shm_alloc(100);
	
	printf("shmalloc addr 0x%x\r\n", addr);

	//int fd = open("/");
	
	//int fd = fopen("STDIN", 0);
	
	//rt_kprintf("shmalloc addr 0x%x\r\n", addr);

	char* dataPtr = (char*)addr;

	for(int k = 0; k < 26; ++k) {
		*dataPtr++ = 'a' + k;
	}
	*dataPtr = '\0';

	rt_kprintf("thread print: %s\r\n", (char *)addr);


	thread = rt_thread_create("inlwp", lwt_thread_entry, (void*)addr, 0x400, 29, 200);
	if(thread == RT_NULL)
	{
		syscall(0x21,0x00);
		return 0;
	}
	rt_thread_startup(thread);

	for(int i = 0; i < 3; ++i) {
		rt_thread_mdelay(800);
		rt_kprintf("shm thread tick %d\r\n", i);
	}

	rt_err_t res = lwt_shm_free((void *)addr);

    rt_kprintf("free result %d\r\n", res);
	
	return 0;//需要重定义sys_exit 否则会出现软件中断
}
