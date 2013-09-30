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

struct virgo_mempool_args
{
	char* mempool_cmd;
	char* mempool_args[3];
};

char* toAddress(char*);
void* virgo_cloud_malloc(void*);
void* virgo_cloud_free(void*);
void* virgo_cloud_get(void*);
void* virgo_cloud_set(void*);
struct virgo_mempool_args* parse_virgomempool_command_userspace(char* mempoolFunction);

void* virgo_cloud_malloc(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_malloc(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_userspace((char*)args);
	int size=atoi(vmargs->mempool_args[0]);
	void* ptr=malloc(size);
	printf("virgo_cloud_mempool.c:virgo_cloud_malloc(): ptr=%p\n",ptr);
	fflush(stdout);
	return ptr;
}

void* virgo_cloud_get(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_get(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_userspace((char*)args);
	char* ptr=toAddress((char*)vmargs->mempool_args[0]);	
	printf("virgo_cloud_mempool.c: virgo_cloud_get(): address=%p, data=%s\n",ptr,ptr);
	return ptr;
}

void* virgo_cloud_set(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_set(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_userspace((char*)args);
	char* ptr=toAddress(vmargs->mempool_args[0]);
	strcpy(ptr,strdup(vmargs->mempool_args[1]));
	printf("virgo_cloud_mempool.c: virgo_cloud_set(): address=%p, data=%s\n",ptr,vmargs->mempool_args[1]);
	return 0;
}

void* virgo_cloud_free(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_free(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_userspace((char*)args);
	char* ptr=toAddress(vmargs->mempool_args[0]);
	printf("virgo_cloud_mempool.c: virgo_cloud_free(): address=%p\n",ptr);
	free(ptr);
	return 0;
}

struct virgo_mempool_args* parse_virgomempool_command_userspace(char* mempoolFunction)
{
        struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)malloc(sizeof(struct virgo_mempool_args));
        vmargs->mempool_cmd=strdup(strsep(&mempoolFunction, "("));
        if(strcmp(vmargs->mempool_cmd,"virgo_cloud_malloc")==0 || strcmp(vmargs->mempool_cmd,"virgo_cloud_free")==0)
        {
                vmargs->mempool_args[0]=strdup(strsep(&mempoolFunction,")"));
                vmargs->mempool_args[1]=NULL;
        }
        else
        {

                vmargs->mempool_args[0]=strdup(strsep(&mempoolFunction,","));
                vmargs->mempool_args[1]=strdup(strsep(&mempoolFunction,")"));
                vmargs->mempool_args[2]=NULL;
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
