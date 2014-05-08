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
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct virgo_fs_args
{
	char* fs_cmd;
	char* fs_args[3];
};

struct virgo_fs_args* parse_virgofs_command_userspace(char* fsFunction);
void* virgo_cloud_open(void*);
void* virgo_cloud_close(void*);
void* virgo_cloud_read(void*);
void* virgo_cloud_write(void*);

void* virgo_cloud_open(void* args)
{
	char buf[500];
	printf("virgo_cloud_fs.c:Executing virgo_cloud_fs on cloud node, Invoking virgo_cloud_open(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_fs_args* vmargs=parse_virgofs_command_userspace((char*)args);
	int fd=open(vmargs->fs_args[0],O_RDWR);
	read(fd,buf,500);	
	printf("virgo_cloud_fs.c:virgo_cloud_open(): fd=%d,buf=%s\n",fd,buf);
	fflush(stdout);
	return &fd;
}

void* virgo_cloud_read(void* args)
{
	printf("virgo_cloud_fs.c:Executing virgo_cloud_fs on cloud node, Invoking virgo_cloud_read(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_fs_args* vmargs=parse_virgofs_command_userspace((char*)args);
	char buf[256];
	int fd=atoi(vmargs->fs_args[0]);
	fd=open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgofstest.txt",O_RDWR);
	read(fd,buf,256);	
	printf("virgo_cloud_fs.c: virgo_cloud_read(): fd=%d, buf=%s\n",fd,buf);
	return NULL;
}

void* virgo_cloud_write(void* args)
{
	printf("virgo_cloud_fs.c:Executing virgo_cloud_fs on cloud node, Invoking virgo_cloud_write(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_fs_args* vmargs=parse_virgofs_command_userspace((char*)args);
	int fd=atoi(vmargs->fs_args[0]);
	printf("virgo_cloud_fs.c: virgo_cloud_write(): buf=%s\n",vmargs->fs_args[1]);
	fd=open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgofstest.txt",O_RDWR);
	write(fd,vmargs->fs_args[1],256);	
	fsync(fd);
	return NULL;
}

void* virgo_cloud_close(void* args)
{
	printf("virgo_cloud_fs.c:Executing virgo_cloud_fs on cloud node, Invoking virgo_cloud_close(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_fs_args* vmargs=parse_virgofs_command_userspace((char*)args);
	int fd=atoi(vmargs->fs_args[0]);
	close(fd);
	return NULL;
}

struct virgo_fs_args* parse_virgofs_command_userspace(char* fsFunction)
{
        struct virgo_fs_args* vmargs=(struct virgo_fs_args*)malloc(sizeof(struct virgo_fs_args));
	printf("virgo_cloud_fs.c:fsFunction to parse = %s\n",fsFunction);
        vmargs->fs_cmd=strdup(strsep(&fsFunction, "("));
	printf("virgo_cloud_fs.c:vmargs->fs_cmd = %s\n",vmargs->fs_cmd);
        if(strcmp(vmargs->fs_cmd,"virgo_cloud_open")==0 || strcmp(vmargs->fs_cmd,"virgo_cloud_close")==0)
        {
                vmargs->fs_args[0]=strdup(strsep(&fsFunction,")"));
		printf("virgo_cloud_fs.c:vmargs->fs_args[0] = %s\n",vmargs->fs_args[0]);
                vmargs->fs_args[1]=NULL;
        }
        else
        {

                vmargs->fs_args[0]=strdup(strsep(&fsFunction,","));
                vmargs->fs_args[1]=strdup(strsep(&fsFunction,","));
                vmargs->fs_args[2]=strdup(strsep(&fsFunction,")"));
		printf("virgo_cloud_fs.c:vmargs->fs_args[0] = %s\n",vmargs->fs_args[0]);
		printf("virgo_cloud_fs.c:vmargs->fs_args[1] = %s\n",vmargs->fs_args[1]);
		printf("virgo_cloud_fs.c:vmargs->fs_args[2] = %s\n",vmargs->fs_args[2]);
                vmargs->fs_args[3]=NULL;
        }
        return vmargs;
}

/*
This function parses the address within the string strAddress and returns as the address
Example: "0x0000ffff" to 0x0000ffff
*/

char* toAddress(char* strAddress)
{
	char *ptr=NULL;
	sscanf(strAddress,"%p",ptr);	
	return ptr;
}
