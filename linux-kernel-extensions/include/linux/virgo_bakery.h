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

#ifndef _VIRGO_BAKERY_H_
#define _VIRGO_BAKERY_H_

#include <linux/ioport.h>
#include <linux/kobject.h>
#include <linux/klist.h>
#include <linux/list.h>
#include <linux/lockdep.h>
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/pm.h>
#include <linux/atomic.h>
#include <linux/ratelimit.h>
#include <asm/device.h>

/******************************************/

#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/file.h>
#include <linux/freezer.h>
#include <net/sock.h>
#include <net/checksum.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/tcp.h>
#include <net/tcp_states.h>
#include <asm/uaccess.h>
#include <asm/ioctls.h>
#include <trace/events/skb.h>

#include <linux/module.h>
#include <linux/types.h>
#include <linux/uio.h>
#include <linux/unistd.h>
/*#include <linux/init.h>*/

#include <linux/sunrpc/types.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sunrpc/xdr.h>
#include <linux/sunrpc/msg_prot.h>
#include <linux/sunrpc/svcsock.h>
#include <linux/sunrpc/stats.h>
#include <linux/sunrpc/xprt.h>
/*#include "sunrpc.h"*/
#include <linux/sunrpc/xprt.h>
/*#include "netns.h"*/




/* Maximum number of concurrent threads that contend for critical section */
#define MAX_CONCURRENT_THREADS 2 

/* For each thread boolean flag array to indicate if in critical section or not */
int in_critical_section[MAX_CONCURRENT_THREADS];

/* Token Number assigned by the cloud node service for each client threads */
int *token;

int virgobakery_threadfunc1(void* args);
int virgobakery_threadfunc2(void* args);

int shared=0;

int maximum_of(int*);

/* 
Lock and Unlock - 0 <= thread_id < MAX_CONCURRENT_THREADS
Locking has three phases of entering critical section:
- Phase 1 : the unique token number is allotted for each thread and thread exits the Phase 1 of critical section
- Phase 2 : Only threads with unique number enter the third phase and other threads spinwait in second phase. 
- Phase 3 : Only thread with (thread_id, token[thread_id]) < (i, token[i]) for all threads i gets the critical section and others spinwait

bakery_lock() has two parameters - thread id and flag for textbook version of one for loop (this causes a serious system freeze,not sure of the reason) or modified version in VIRGO Linux that has two for loops (which seems to work)
*/

void bakery_lock(int thread_id, int oneforloop)
{

	/* Phase 1 */	
	token=kzalloc(sizeof(int)*MAX_CONCURRENT_THREADS, GFP_ATOMIC);
	in_critical_section[thread_id]=1;
	token[thread_id] = 1 + maximum_of(token);
	printk(KERN_INFO "bakery_lock(): phase 1, token[thread_id] = %d \n", token[thread_id]);
	in_critical_section[thread_id]=0;

	/* Phase 2 */
	int i;
	if(oneforloop)
	{
		/* one for loop - standard textbook version - this causes kernel freeze - soft lockup errors - and panic more often */
		for(i=0 ; i < MAX_CONCURRENT_THREADS; i++)
		{
			printk(KERN_INFO "bakery_lock(): phase 2 \n");
			while(in_critical_section[i] == 1)
				;
			/* Phase 3 - only thread id(s) with unique numbers */
			/* 
			All threads are queued and this thread spinwaits till all the other threads have smaller token numbers implying
			they are chronologically more prioritizable to this thread. As other threads finish, their tokens are set to zero
			and eventually this thread is in front of the queue and its token is smallest thus having biggest priority.
			*/
			printk(KERN_INFO "bakery_lock(): phase 3 \n");
			while(token[i] != 0 && ((token[thread_id] > token[i]) || ((token[thread_id] == token[i]) && (thread_id > i))))
			{
				printk(KERN_INFO "bakery_lock(): Phase 3: spinwait ...... token[i] = %d, token[thread_id] = %d, i = %d, thread_id=%d\n", token[i], token[thread_id], i, thread_id);
			}
			printk(KERN_INFO "bakery_lock() - oneforloop: thread %d entering critical section, token for this thread %d \n", thread_id, token[thread_id]);
		}
	}
	else
	{
		/* two for loops - VIRGO Linux version - this causes kernel freeze - soft lockup errors - and panic sometimes */	
		for(i=0 ; i < MAX_CONCURRENT_THREADS; i++)
		{
			while(in_critical_section[i] == 1)
				;
		}
	
		/* Phase 3 - only thread id(s) with unique numbers */
		/* 
		All threads are queued and this thread spinwaits till all the other threads have smaller token numbers implying
		they are chronologically more prioritizable to this thread. As other threads finish, their tokens are set to zero
		and eventually this thread is in front of the queue and its token is smallest thus having biggest priority.
		*/
		for(i=0 ; i < MAX_CONCURRENT_THREADS; i++)
		{
			while((token[i] != 0) && (token[thread_id] > token[i]) || (token[thread_id] == token[i] && thread_id > i))
				;
			printk(KERN_INFO "bakery_lock() - twoforloops: thread %d entering critical section, token for this thread %d \n", thread_id, token[thread_id]);
		}
	}
}

void bakery_unlock(int thread_id)
{
	/*
	in_critical_section[thread_id]=0;
	*/
	token[thread_id]=0;
	printk(KERN_INFO "bakery_unlock(): thread %d exiting critical section, token for this thread %d", thread_id, token[thread_id]);
}

int maximum_of(int* t)
{
	int max=-1;
	int i;
	for(i=0; i < MAX_CONCURRENT_THREADS; i++)
	{
		if(t[i] > max)
		{
			printk(KERN_INFO "maximum_of(): token[i] = %d \n", t[i]);
			max=t[i];	
		}
	}
	printk(KERN_INFO "maximum_of(): token[i] = %d \n", max);
	return max;
}

#endif
