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
#include <linux/virgo_mempool.h>
#include <linux/string.h>


char* toKernelAddress(const char*);
int toInteger(char*);
void* virgo_cloud_malloc_kernelspace(struct virgo_mempool_args*);
void* virgo_cloud_free_kernelspace(struct virgo_mempool_args*);
void* virgo_cloud_get_kernelspace(struct virgo_mempool_args*);
void* virgo_cloud_set_kernelspace(struct virgo_mempool_args*);
struct virgo_mempool_args* parse_virgomempool_command_kernelspace(char* mempoolFunction);

static int __init
virgo_cloud_mempool_kernelspace_init(void)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace_init(): doing init() of virgo cloud kernel space test module\n");
	unsigned long test_ul;
	char* test_str="ef098363";
	kstrtoul(test_str,16,&test_ul);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace_init(): test_str=%s, test_ul=%u\n",test_str,test_ul);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_init);


static void __exit
virgo_cloud_mempool_kernelspace_exit(void)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace_exit(): exiting virgo cloud test kernel space module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgo_cloud_mempool_kernelspace_exit);



void* virgo_cloud_malloc_kernelspace(struct virgo_mempool_args* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_malloc_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	/*struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);*/
	struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)args;
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): size str=%s\n",vmargs->mempool_args[0]);

	int size=toInteger(vmargs->mempool_args[0]);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): size=%d\n",size);
	void* ptr=kmalloc(size,GFP_KERNEL);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): ptr=%p\n",ptr);
	vmargs->ptr=(char*)ptr;
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:virgo_cloud_malloc_kernelspace(): setting ptr=%p in vmargs as an out arg\n",ptr);
	return ptr;
}
EXPORT_SYMBOL(virgo_cloud_malloc_kernelspace);

void* virgo_cloud_get_kernelspace(struct virgo_mempool_args* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_get_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	/*struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);*/
	struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)args;
	char* ptr=toKernelAddress((const char*)vmargs->mempool_args[0]);	
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_get_kernelspace(): address=%p, data=%s\n",ptr,ptr);
	return ptr;
}
EXPORT_SYMBOL(virgo_cloud_get_kernelspace);

void* virgo_cloud_set_kernelspace(struct virgo_mempool_args* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_set_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	/*struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);*/
	struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)args;
	printk(KERN_INFO "virgo_cloud_set_kernelspace(): vmargs->mempool_cmd=%s, vmargs->mempool_args[0] = %s\n, vmargs->mempool_args[1]=%s \n",vmargs->mempool_cmd, vmargs->mempool_args[0],vmargs->mempool_args[1]);
	char* ptr=toKernelAddress((const char*)vmargs->mempool_args[0]);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: ptr set by toKernelAddress=%p\n",ptr);
	strcpy(ptr,kstrdup(vmargs->mempool_args[1],GFP_KERNEL));
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_set_kernelspace(): address=%p, data to be set=%s, data after set=%s\n",ptr,vmargs->mempool_args[1], ptr);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_set_kernelspace);

void* virgo_cloud_free_kernelspace(struct virgo_mempool_args* args)
{
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c:Executing virgo_cloud_mempool on cloud node, Invoking virgo_cloud_free_kernelspace(), Writing to file opened by Kernel, Kernel Space to User space communication works\n");
	/*struct virgo_mempool_args* vmargs=parse_virgomempool_command_kernelspace((char*)args);*/
	struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)args;
	char* ptr=toKernelAddress(vmargs->mempool_args[0]);
	printk(KERN_INFO "virgo_cloud_mempool_kernelspace.c: virgo_cloud_free_kernelspace(): address=%p\n",ptr);
	kfree(ptr);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_free_kernelspace);

/*
/struct virgo_mempool_args* parse_virgomempool_command_kernelspace(char* mempoolFunction)/
struct virgo_mempool_args* parse_virgomempool_command_kernelspace(void* args)
{
	/
        struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)kmalloc(sizeof(struct virgo_mempool_args),GFP_KERNEL);
	/
	struct virgo_mempool_args* vmargs=(struct virgo_mempool_args*)args;
	/
        vmargs->mempool_cmd=kstrdup(strsep(&mempoolFunction, "("),GFP_KERNEL);
	/
        if(strcmp(vmargs->mempool_cmd,"virgo_cloud_malloc")==0 || strcmp(vmargs->mempool_cmd,"virgo_cloud_free")==0)
        {
                vmargs->mempool_args[0]=kstrdup(strsep(&mempoolFunction,")"),GFP_KERNEL);
                vmargs->mempool_args[1]=NULL;
        }
        else
        {

                vmargs->mempool_args[0]=kstrdup(strsep(&mempoolFunction,","),GFP_KERNEL);
                vmargs->mempool_args[1]=kstrdup(strsep(&mempoolFunction,")"),GFP_KERNEL);
                vmargs->mempool_args[2]=NULL;
        }
        return vmargs;
}
*/

/*
This function parses the address within the string strAddress and returns as the kernel address
Example: "0x0000ffff" to 0x0000ffff
*/

char* toKernelAddress(const char* strAddress)
{
	char *ptr=NULL;
	char* strAddress1="ef098363";
	char* strAddress2="ef098363";

	sscanf(strAddress1,"%p",(void**)&ptr);	
        printk(KERN_INFO "toKernelAddress(): sscanf: strAddress1=[%s], ptr = %p\n", strAddress1, ptr);

	/*
	added simple_strtoll() as done in virgo_malloc.c syscall client
	as sscanf returns null similar to virgo_malloc.c.
	simple_strtoul() is sscanf internal call which is deeper than sscanf.
	- Ka.Shrinivaasan 25October2013, 31October2013
	*/
	char* endptr;
        printk(KERN_INFO "toKernelAddress(): before simple_strtoul: strAddress1=[%s] \n",strAddress1);
        unsigned long ul1=simple_strtoul(strAddress1, &endptr, 16);
	void* voidptr_ul1=(void*)ul1;
        printk(KERN_INFO "toKernelAddress(): after simple_strtoul: strAddress1=[%s], (void*)ul1=%p, ul1=%u\n", strAddress1, voidptr_ul1, ul1);

	unsigned long ul;
	kstrtoul(strAddress2,16,&ul);
	void* voidptr_ul=(void*)ul;
        printk(KERN_INFO "toKernelAddress(): kstrtoul: ul=%u, (void*)ul=%p,strAddress2=[%s]", ul, voidptr_ul, strAddress2);
	/*
        char* ultovoidptr= (char*)ul;
        printk(KERN_INFO "toKernelAddress(): after cast: kstrtoul: ul=%u, strAddress=[%s], ultovoidptr = %p\n", ul, strAddress, ultovoidptr);
	if(ultovoidptr)
	{
        	return ultovoidptr;
	}
	else
		return ptr;
	*/
	return (char*)voidptr_ul;
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
