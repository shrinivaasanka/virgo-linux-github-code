/***************************************************************************************
VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------------------
Copyright (C):
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Independent Open Source Developer, Researcher and Consultant
Ph: 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	/*
 	int fd=open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt",O_RDWR | O_APPEND);
	char buf[500];
        sprintf(buf,"virgo_cloud_mempool: executing userspace thread for virgo_cloud_mempool on virgo cloud\n");
        write(fd,buf,sizeof(buf));

        fsync(fd);
        close(fd);
	*/
	int pid;
	int x=100;
	int status;
	x=x*x;
	pid=fork();
	void* ptr;
	if(pid==0)
	{
		/*
		int fd=open("./virgo_cloud_mempool_print_to_stdout.out", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
		dup2(fd,1);
		dup2(fd,2);
		*/
		printf("Child process of fork: virgo_cloud_mempool_main.c: User space has written to a VFS file opened by Kernel, Kernel To User space communication worksi. Doing userspace malloc(1000)\n");
		ptr=malloc(1000);
		fflush(stdout);
		x=x*x;
	}
	else
	{
		/*
		int fd=open("./virgo_cloud_mempool_print_to_stdout.out", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
		dup2(fd,1);
		dup2(fd,2);
		*/
		printf("Parent process of fork: virgo_cloud_mempool_main.c: User space has written to a VFS file opened by Kernel, Kernel To User space communication works\n");
		fflush(stdout);
		x=x*x;
		waitpid(pid,&status,WCONTINUED);
	}
	return NULL;
}
