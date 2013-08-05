/***************************************************************************************
VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities

Copyright (C) 2009-2013  Ka.Shrinivaasan

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

mail to: ka.shrinivaasan@gmail.com
*****************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void* virgo_cloud_test(void*);

void* virgo_cloud_test(void* args)
{
	/*
 	int fd=open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt",O_RDWR | O_APPEND);
	char buf[500];
        sprintf(buf,"virgo_cloud_test: executing userspace thread for virgo_cloud_test on virgo cloud\n");
        write(fd,buf,sizeof(buf));

        fsync(fd);
        close(fd);
	*/
	printf("virgo_cloud_test.c:Executing virgo_cloud_test on cloud, Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	fflush(stdout);
	return NULL;
}
