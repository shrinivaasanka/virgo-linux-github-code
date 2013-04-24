#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	long int ret=syscall(350,"int clone_func(void* args)",NULL,0,NULL);
	return 0;
}
