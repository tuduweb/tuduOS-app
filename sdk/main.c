#include "retarget.h"
#include "stdint.h"
#include "bin_mem.h"

#define HEAP_SIZE  0x4000
#define STACK_SIZE 0x400
__attribute__((used)) __attribute__((section("HEAP"))) __attribute__((zero_init)) static char app_heap[HEAP_SIZE];
__attribute__((used)) __attribute__((section("STACK"))) __attribute__((zero_init))  static char app_stack[STACK_SIZE];

void lwt_thread_entry(void* parameter)
{
    syscall(0x21,1234);
	while(1);
}

rt_thread_t thread;




int main(int argc, const char **argv, const char **envp){

	app_heap_init(app_heap, app_heap + HEAP_SIZE);

	//int cnt = 0;
	//int i = 0;
	// rt_thread_t thread;
	// for(;i < 3;i++)
	// {
	// 	syscall(0x21,cnt++);
	// }

	//测试
	syscall(0x21,0x99);

	//uint32_t* pointer = (uint32_t*)0x70000004;
	//*pointer = 1;
	
	//printf("test");
	
	thread = rt_thread_create("inlwp", lwt_thread_entry, 0, 0x400, 29, 200);
	rt_thread_startup(thread);

	char* txt;
	txt = malloc(100);

	for(int i = 0;i < 100; ++i)
	{
		*(txt + i) = '#';
	}


	while(1);
	
	return 0;//需要重定义sys_exit 否则会出现软件中断
}


// int $Sub$$main(int argc, const char **argv, const char **envp)
// {
// 	app_heap_init(heap, heap + HEAP_SIZE);

// 	return main(argc, argv, envp);

// }

