#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	/*
	long int ret=syscall(350,"int clone_func(void* args)",NULL,0,NULL);
	*/

	/*
	Mangled name for function prototype "void* virgo_cloud_test(void*)" is sent to virgo_cloudexec kernel service which does
	upcall to userspace to invoke the function (within libvirgo.so) in remote cloud node. Kernel upcall usermode helper 
	requires mangled names for dlsym(). This also is a unique id for a function. Library libvirgo.so needs to be prebuilt
	with all functions that need to be on cloud and should be replicated in all cloud nodes.
	Padded right with 2 whitespaces for ^M removal code in kernel module side.
	- Ka.Shrinivaasan
	*/
	/*long int ret=syscall(350,"_Z16virgo_cloud_testPv  ",NULL,0,NULL);*/
	long int ret=syscall(350,argv[1],NULL,0,NULL);
	return 0;
}
