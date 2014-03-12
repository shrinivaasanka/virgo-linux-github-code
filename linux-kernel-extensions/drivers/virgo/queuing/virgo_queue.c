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
Ph: 9789346927, 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): 
http://sourceforge.net/users/ka_shrinivaasan,
https://www.ohloh.net/accounts/ka_shrinivaasan 
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

/* 
	A standalone Queueing Driver implementation which either uses a kernel workqueue or a naive local queue
	that can be used for VIRGO CPU and Memory pooling Drivers requests and  
	KingCobra byzantine request servicing pub-sub model
*/

#include <linux/virgo_queue.h>


static int __init virgo_queue_init()
{
	virgo_request_queue=kmalloc(VIRGO_QUEUE_SZ, GFP_KERNEL);
	struct virgo_request r1;
	r1.data=kstrdup("example virgo queue element 1",GFP_KERNEL);
	r1.next=NULL;
	push_request(&r1);

	/* Simple push-pop test */

	printk(KERN_INFO "virgo_queue_init(): pushed element to native virgo_queue: %s\n",r1.data);
	struct virgo_request *r2=pop_request();
	printk(KERN_INFO "virgo_queue_init(): popped element from native virgo_queue: %s\n",r2->data);

	/* Linux workqueue has to be differently queued-in and there need not be any explicit push and pop */
	if(use_workqueue)
	{
		printk(KERN_INFO "virgo_queue_init(): use_workqueue=1");
		if(virgo_kernel_wq==NULL)
		{
			printk(KERN_INFO "virgo_queue_init(): use_workqueue=1, virgo_kernel_wq=NULL, creating a kernel workqueue");
			virgo_kernel_wq = create_workqueue("virgo_kernel_workqueue");
		}
		printk(KERN_INFO "virgo_queue_init(): use_workqueue=1, enqueueing work to kernel workqueue");
		queue_work(virgo_kernel_wq, &virgo_work);
	}
	return 0;
}

void push_request(struct virgo_request* req)
{
	virgo_request_queue[queue_end].data=kstrdup(req->data,GFP_KERNEL);
	virgo_request_queue[queue_end].next=req->next;
	queue_end++;
}
EXPORT_SYMBOL(push_request);

struct virgo_request* pop_request()
{
	return &virgo_request_queue[queue_front];
	queue_front++;
}
EXPORT_SYMBOL(pop_request);

static void __exit virgo_queue_exit()
{
	do_exit(1);
}

MODULE_LICENSE("GPL");
module_init(virgo_queue_init);
module_exit(virgo_queue_exit);
