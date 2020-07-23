extern int syscall(int number, ...);
int main(){
	int cnt = 0;
	for(int i = 0;i < 3;i++)
	{
		syscall(0x21,cnt++);
	}
	
	return 0;
}
