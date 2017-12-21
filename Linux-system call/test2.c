#include<unistd.h>
#include<stdio.h>

int main(){
	int pid=getpid();
	int prio, nice, x;
	x = syscall(334, pid, 0, 0, &prio, &nice);
	printf("pid=%d, prioprity = %d, nice = %d\n", pid, prio, nice);

	x = syscall(334, pid, 1, 2, &prio, &nice);
	printf("pid=%d, priority = %d, nice = %d\n", pid, prio, nice);
	return 0;
}
