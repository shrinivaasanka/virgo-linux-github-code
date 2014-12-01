/************************************************************************************************
#ASFER - a ruleminer which gets rules specific to a query and executes them (component of iCloud Platform)
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#---------------------------------------------------------------------------------------------------------
#Copyright (C):
#Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
#Ph: 9789346927, 9003082186, 9791165980
#Krishna iResearch Open Source Products Profiles: 
#http://sourceforge.net/users/ka_shrinivaasan, https://www.openhub.net/accounts/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#ZODIAC DATASOFT: https://github.com/shrinivaasanka/ZodiacDatasoft
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
#---------------------------------------------------------------------------------------------------------
**************************************************************************************************/


/*
Experimental - Bakery Algorithm Implementation for VIRGO Cloud
--------------------------------------------------------------

1.lock():
	- Each thread i gets a unique number - 1 + max(already assigned)
	- for all threads k:
		 spinlock_till([i,num(i)] < [k,num(k)]
		 { i < k or (i==k and num(i) < num(k)) }

2.unlock():
	- Discard unique number

For cloud synchronization, above unique id can also be augmented with ip address and timestamp optionally. 
*/

#include <linux/virgo_bakery.h>

static int __init
virgobakery_init(void)
{
        printk(KERN_INFO "virgobakery_init(): initializing virgo bakery kernel module datastructures \n");
        /*
        printk(KERN_INFO "virgobakery_init(): invoking read_virgo_config()\n");
        read_virgo_config();
        */

	int i;
	for(i=0; i < MAX_CONCURRENT_THREADS; i++)
	{
		in_critical_section[i]=0;
		/*token[i]=0;*/
	}

	int* thread_id1=kmalloc(sizeof(int),GFP_ATOMIC);
	int* thread_id2=kmalloc(sizeof(int),GFP_ATOMIC);
	struct task_struct *task1;
	struct task_struct *task2;
	*thread_id1=1;
        int woken_up=0;
       
	printk(KERN_INFO "virgobakery_init(): creating kernel thread 1\n");
        task1=kthread_create(virgobakery_threadfunc1, NULL, "virgo_bakery thread 1");
        woken_up=wake_up_process(task1);
       
	*thread_id2=2;
	printk(KERN_INFO "virgobakery_init(): creating kernel thread 2\n");
        task2=kthread_create(virgobakery_threadfunc2, NULL, "virgo_bakery thread 2");
        woken_up=wake_up_process(task2);
        return 0;
}
EXPORT_SYMBOL(virgobakery_init);

int virgobakery_threadfunc1(void* args)
{
	int i;
	
	for(i=0; i < 10; i++)
	{
		/* one for loop in lock */
		bakery_lock(0, 1);
		shared=100;
		printk(KERN_INFO "virgobakery_threadfunc1(): bakery_lock_oneforloop: shared = %d; kernel thread %d function \n", shared, 0);
		bakery_unlock(0);
	}
	return 0;
}

int virgobakery_threadfunc2(void* args)
{
	int i;

	for(i=0; i < 10; i++)
	{
		/* one for loop in lock */
		bakery_lock(1, 1);
		shared=200;
		printk(KERN_INFO "virgobakery_threadfunc2(): bakery_lock_oneforloop: shared = %d; kernel thread %d function \n", shared, 1);
		bakery_unlock(1);
	}
	return 0;
}

static void __exit
virgobakery_exit(void)
{
        printk(KERN_INFO "exiting virgo bakery kernel module \n");
        /*filp_close(file_stdout,NULL);*/
        do_exit(1);
}
EXPORT_SYMBOL(virgobakery_exit);


MODULE_LICENSE("GPL");
module_init(virgobakery_init);
module_exit(virgobakery_exit);
                             
