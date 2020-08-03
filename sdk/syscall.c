/**
 * SYSCALL 系统调用
 * 实现需要调用的函数，和syscall包装成中间函数
 * @param number 系统调用号
 * @return 状态标致
 */
int syscall_c(int number, ...){
	__asm("svc 0x00");
	return 0;
}
