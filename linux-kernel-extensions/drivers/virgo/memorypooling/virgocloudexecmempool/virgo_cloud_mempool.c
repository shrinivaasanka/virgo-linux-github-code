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
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct virgo_set_args
{
	char* addr;
	char* data;
};

void* virgo_cloud_malloc(void*);
void* virgo_cloud_free(void*);
void* virgo_cloud_get(void*);
void* virgo_cloud_set(void*);

void* virgo_cloud_malloc(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_malloc(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	int size=*((int*)(args));
	void* ptr=malloc(size);
	printf("virgo_cloud_mempool.c:virgo_cloud_malloc(): ptr=%p\n",ptr);
	fflush(stdout);
	return ptr;
}

void* virgo_cloud_get(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_get(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	char* ret=strdup((char*)args);	
	printf("virgo_cloud_mempool.c: virgo_cloud_get(): address=%p, data=%s\n",(char*)args,ret);
	return ret;
}

void* virgo_cloud_set(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_set(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_set_args *vsetargs=(struct virgo_set_args*)args;
	vsetargs->addr=strdup(vsetargs->data);
	printf("virgo_cloud_mempool.c: virgo_cloud_set(): address=%p, data=%s\n",vsetargs->addr,vsetargs->data);
	return 0;
}

void* virgo_cloud_free(void* args)
{
	printf("virgo_cloud_mempool.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_free(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	char* ptr=(char*)args;
	printf("virgo_cloud_mempool.c: virgo_cloud_free(): address=%p\n",ptr);
	return 0;
	free(ptr);
	return 0;
}
