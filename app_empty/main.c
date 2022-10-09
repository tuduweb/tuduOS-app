#include "retarget.h"
#include "stdint.h"
#include "bin_mem.h"

#define HEAP_SIZE  0x2000
#define STACK_SIZE 0x200
__attribute__((used)) __attribute__((section("HEAP"))) __attribute__((zero_init)) static char app_heap[HEAP_SIZE];
__attribute__((used)) __attribute__((section("STACK"))) __attribute__((zero_init))  static char app_stack[STACK_SIZE];

rt_mailbox_t mb;

int lwt_thread_entry(void* parameter)
{
	int cnt = 0;
    syscall(0x21,1234);
	while(1)
	{
		syscall(0x21,cnt++);
		rt_thread_mdelay(2000);
		if(cnt == 5)
		{
			rt_mb_send(mb, 666);
		}else if(cnt > 5)
		{
			break;
		}
	}
	return 0;
}

rt_thread_t thread = 0;




int main(int argc, const char **argv, const char **envp){
	
	rt_ubase_t msg = 0;

	app_heap_init(app_heap, app_heap + HEAP_SIZE);

	rt_kprintf("hello world!\r\n");
    
	return 0;
}


// int $Sub$$main(int argc, const char **argv, const char **envp)
// {
// 	app_heap_init(heap, heap + HEAP_SIZE);

// 	return main(argc, argv, envp);

// }

