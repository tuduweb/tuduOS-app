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

	//int cnt = 0;
	//int i = 0;
	// rt_thread_t thread;
	// for(;i < 3;i++)
	// {
	// 	syscall(0x21,cnt++);
	// }

	//测试
	syscall(0x21,0x99);

	mb = rt_mb_create("lwp", 1, RT_IPC_FLAG_FIFO);

	thread = rt_thread_create("inlwp", lwt_thread_entry, 0, 0x400, 29, 200);
	if(thread == RT_NULL)
	{
		syscall(0x21,0x00);
		return 0;
	}
	rt_thread_startup(thread);

	int cnt = 9999;

	while(1)
	{
		if(rt_mb_recv(mb, &msg, RT_WAITING_FOREVER) == RT_EOK)
		{
			syscall(0x21,msg);
			rt_mb_delete(mb);//删除，防止溢出(所以要在线程销毁的时候,加上销毁所有生产的资源…)
			break;
		}
		syscall(0x21,cnt--);
	}
	
	return 0;//需要重定义sys_exit 否则会出现软件中断
}


// int $Sub$$main(int argc, const char **argv, const char **envp)
// {
// 	app_heap_init(heap, heap + HEAP_SIZE);

// 	return main(argc, argv, envp);

// }

