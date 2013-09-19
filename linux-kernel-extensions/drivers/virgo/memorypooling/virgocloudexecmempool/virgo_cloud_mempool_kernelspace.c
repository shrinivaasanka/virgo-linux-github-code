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


#include <linux/string.h>
#include <linux/module.h>
#include <linux/virgo.h>

struct virgo_set_args
{
        char* addr;
        char* data;
};


static int __init
virgo_cloud_mempool_kernelspace_init(void)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace_init(): doing init() of virgo cloud kernel space test module\n");
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_init);

void* virgo_cloud_malloc_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_malloc_kernelspace(): virgo cloud kernel space test function invoked in this module by virgo_cloudexec kernel service\n");
	int size=*((int*)(args));
	void* ptr=kmalloc(size, GFP_ATOMIC);
	return ptr;
}
EXPORT_SYMBOL(virgo_cloud_malloc_kernelspace);

void* virgo_cloud_free_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_malloc_kernelspace(): virgo cloud kernel space test function invoked in this module by virgo_cloudexec kernel service\n");
	char* ptr=(char*)(args);
	kfree(ptr);
	return NULL;
}
EXPORT_SYMBOL(virgo_cloud_free_kernelspace);

void* virgo_cloud_set_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_malloc_kernelspace(): virgo cloud kernel space test function invoked in this module by virgo_cloudexec kernel service\n");
	struct virgo_set_args* vsetargs=(struct virgo_set_args*)args;
	vsetargs->addr=kstrdup(vsetargs->data,GFP_ATOMIC);
	return NULL;
}
EXPORT_SYMBOL(virgo_cloud_set_kernelspace);


void* virgo_cloud_get_kernelspace(void* args)
{
	printk(KERN_INFO "virgo_cloud_malloc_kernelspace(): virgo cloud kernel space test function invoked in this module by virgo_cloudexec kernel service\n");
	char* data=kstrdup((char*)args,GFP_ATOMIC);
	return data;
}
EXPORT_SYMBOL(virgo_cloud_get_kernelspace);

static void __exit
virgo_cloud_mempool_kernelspace_exit(void)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace_exit(): exiting virgo cloud test kernel space module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_exit);


MODULE_LICENSE("GPL");
module_init(virgo_cloud_mempool_kernelspace_init);
module_exit(virgo_cloud_mempool_kernelspace_exit);