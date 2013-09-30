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


#include <linux/string.h>
#include <linux/module.h>
#include <linux/virgo.h>
#include <linux/string.h>


struct virgo_mempool_args
{
	char* mempool_cmd;
	char* mempool_args[3];
};

char* toKernelAddress(char*);
int toInteger(char*);
void* virgo_cloud_malloc_kernelspace(void*);
void* virgo_cloud_free_kernelspace(void*);
void* virgo_cloud_get_kernelspace(void*);
void* virgo_cloud_set_kernelspace(void*);
struct virgo_mempool_args* parse_virgomempool_command_kernelspace(char* mempoolFunction);

static int __init
virgo_cloud_mempool_kernelspace_init(void)
{
	printk(KERN_INFO KERN_INFO "virgo_cloud_mempool_kernelspace_init(): doing init() of virgo cloud kernel space test module\n");
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_init);


static void __exit
virgo_cloud_mempool_kernelspace_exit(void)
{
	printk(KERN_INFO KERN_INFO "virgo_cloud_mempool_kernelspace_exit(): exiting virgo cloud test kernel space module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_exit);



void* virgo_cloud_malloc_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_malloc_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): size str=%s\n",vmargs->mempool_args[0]);

	int size=toInteger(vmargs->mempool_args[0]);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): size=%d\n",size);
	void* ptr=kmalloc(size,GFP_ATOMIC);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): ptr=%p\n",ptr);
	return ptr;
}
EXPORT_SYMBOL(virgo_cloud_malloc_kernelspace);

void* virgo_cloud_get_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_get_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);
	char* ptr=toKernelAddress((char*)vmargs->mempool_args[0]);	
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_get_kernelspace(): address=%p, data=%s\n",ptr,ptr);
	return ptr;
}
EXPORT_SYMBOL(virgo_cloud_get_kernelspace);

void* virgo_cloud_set_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_set_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);
	char* ptr=toKernelAddress(vmargs->mempool_args[0]);
	strcpy(ptr,kstrdup(vmargs->mempool_args[1],GFP_ATOMIC));
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_set_kernelspace(): address=%p, data to be set=%s, data after set=%s\n",ptr,vmargs->mempool_args[1], ptr);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_set_kernelspace);

void* virgo_cloud_free_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_free_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);
	char* ptr=toKernelAddress(vmargs->mempool_args[0]);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_free_kernelspace(): address=%p\n",ptr);
	kfree(ptr);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_free_kernelspace);

struct virgo_mempool_args* parse_virgomempool_command_kernelspace(char* mempoolFunction)
{
        struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)kmalloc(sizeof(struct virgo_mempool_args),GFP_ATOMIC);
        vmargs->mempool_cmd=kstrdup(strsep(&mempoolFunction, "("),GFP_ATOMIC);
        if(strcmp(vmargs->mempool_cmd,"virgo_cloud_malloc")==0 || strcmp(vmargs->mempool_cmd,"virgo_cloud_free")==0)
        {
                vmargs->mempool_args[0]=kstrdup(strsep(&mempoolFunction,")"),GFP_ATOMIC);
                vmargs->mempool_args[1]=NULL;
        }
        else
        {

                vmargs->mempool_args[0]=kstrdup(strsep(&mempoolFunction,","),GFP_ATOMIC);
                vmargs->mempool_args[1]=kstrdup(strsep(&mempoolFunction,")"),GFP_ATOMIC);
                vmargs->mempool_args[2]=NULL;
        }
        return vmargs;
}

/*
This function parses the address within the string strAddress and returns as the kernel address
Example: "0x0000ffff" to 0x0000ffff
*/

char* toKernelAddress(char* strAddress)
{
	char *ptr=NULL;
	sscanf(strAddress,"%p",(void**)&ptr);	
	printk(KERN_INFO "toKernelAddress(): strAddress=[%s], address scanned=%p\n", strAddress, ptr);
	return ptr;
}

int toInteger(char* strInt)
{
	int n;
	sscanf(strInt, "%d", &n);
	printk(KERN_INFO "toInteger(): strInt=[%s], integer=%d\n", strInt, n);
	return n;
}


MODULE_LICENSE("GPL");
module_init(virgo_cloud_mempool_kernelspace_init);
module_exit(virgo_cloud_mempool_kernelspace_exit);
