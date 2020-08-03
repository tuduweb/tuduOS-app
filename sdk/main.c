extern int syscall(int number, ...);

#define HEAP_SIZE  128
#define STACK_SIZE 256
__attribute__((used)) __attribute__((section("STACK"))) __attribute__((zero_init))  static char stack[STACK_SIZE];
__attribute__((used)) __attribute__((section("HEAP"))) __attribute__((zero_init)) static char heap[HEAP_SIZE];

int main(){
	int cnt = 0;
	int i = 0;
	for(;i < 3;i++)
	{
		syscall(0x21,cnt++);
	}
	
	return 0;//需要重定义sys_exit 否则会出现软件中断
}
