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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan, https://www.ohloh.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

/*
	VIRGO queue related datastructures
*/

#ifndef _VIRGO_QUEUE_H_
#define _VIRGO_QUEUE_H_

#define VIRGO_QUEUE_SZ 10000

#include <linux/socket.h>
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
#include <linux/workqueue.h>
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

#include <linux/kingcobra.h>

#define LINUX_KERNEL_4_x_x

int virgoqueue_create(void);
int virgoqueue_recvfrom(struct socket*);
int virgoqueue_sendto(struct socket*);

struct virgoqueue_ops_t {
        int (*virgo_queue_create)(void);
        int (*virgo_queue_recvfrom)(struct socket*);
        int (*virgo_queue_sendto)(struct socket*);
};

static struct virgoqueue_ops_t virgoqueue_ops = {
        .virgo_queue_create = virgoqueue_create,
        .virgo_queue_recvfrom = virgoqueue_recvfrom,
        .virgo_queue_sendto = virgoqueue_sendto,
};

struct virgoqueue_class_t {
        const char* m_virgo_name;
        struct module* m_virgo_owner;
        struct virgoqueue_ops_t* m_virgoqueue_ops;
};

static struct virgoqueue_class_t virgoqueue_class = {
        .m_virgo_name = "virgo queue",
        .m_virgo_owner = THIS_MODULE,
        .m_virgoqueue_ops = &virgoqueue_ops
};


struct virgo_request
{
	char* data;
	struct virgo_request* next;
};

int queue_front=0;
int queue_end=0;

struct virgo_workqueue_request
{
	char* data;
	struct work_struct work;
};

/*
This is a boolean flag that flips between a native local implementation of a queue and a 
linux kernel implementation of workqueue.
*/
int use_workqueue=1;

/*
This is a boolean flag that enables use of VIRGO linux workqueue for KingCobra BFT messaging with queues and arbiters. 
*/
int use_for_kingcobra_messaging=1;

/*
This is boolean flag that enables KingCobra in userspace through upcall from kernel using call_usermodehelper().
Obviously circuitous but might have necessity in some userspace applications. By default, KingCobra is in kernel space.
*/
int kingcobra_in_userspace=0;

/*
Persist KingCobra queue contents to disk - Guaranteed queue vs in-memory queue
with other declarations for file data segment and queue file offset.
*/
int kingcobra_disk_persistence=1;
loff_t request_reply_queue_pos=0;
mm_segment_t fs;

void* work_args;

void virgo_workqueue_handler(struct work_struct* w);
static DECLARE_WORK(virgo_work, virgo_workqueue_handler);
static struct workqueue_struct *virgo_kernel_wq=NULL;

struct file* file_stdout;
int virgoqueue_client_thread(void* args);

/*
This boolean flag determines if VIRGO queue module should be a kernel service or just 
exports push/pop functions for VIRGO cpupooling service which receives requests from
virgo_clone() system call or telnet client. It is required due to a deadlock that occurs
when the VIRGO cpupooling service does a push_request() but VIRGO queue waits in the
reactor pattern loop waiting for incoming requests and eventually there is a symbol lookup error.
If set to 1, it waits for requests as kernel service.
*/
int virgo_queue_reactor_service_mode=0;

int virgoqueue_num_cloud_nodes=0;
char virgoqueue_node_ip_addrs_in_cloud[100];

void virgo_workqueue_handler(struct work_struct* w)
{
	int ret;
	char* argv[5];
	char* envp[5];
	mm_segment_t fs;
	struct virgo_workqueue_request *vwqrq=container_of(w, struct virgo_workqueue_request, work);
	if(vwqrq != NULL && w != NULL )
		printk(KERN_INFO "virgo_workqueue_handler(): invoked for work_struct w=%p, dequeueing enqueued vwqrq->data=%s",w,vwqrq->data);

	/*if(strncmp(vwqrq->data,"KingCobra:",10)==0)*/
	if(use_for_kingcobra_messaging==1)
	{
		if(kingcobra_in_userspace==1)
		{
        		fs=get_fs();
        		set_fs(get_ds());

			file_stdout=filp_open("/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-4.1.5/drivers/kcobra/kingcobra_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
        		fd_install(1,file_stdout);
        		fd_install(2,file_stdout);

			argv[0]="/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-4.1.5/drivers/kcobra/kingcobra_main";
			argv[1]=kstrdup("_Z24KingCobra_ServiceRequestPv",GFP_ATOMIC);
			argv[2]=kstrdup(vwqrq->data,GFP_ATOMIC);
			argv[3]=NULL;

			envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games::/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-4.1.5/drivers/kcobra";
               		envp[1]="HOME=/home/shrinivaasanka";
               		envp[2]=NULL;

			printk(KERN_INFO "virgo_workqueue_handler(): kingcobra_in_userspace=1, before invoking call_usermodehelper() for KingCobra \n");
               		ret=call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
			printk(KERN_INFO "virgo_workqueue_handler(): after invoking call_usermodehelper() for KingCobra, usermode helper ret=%d \n",ret);
			filp_close(file_stdout,NULL);
			set_fs(fs);
		}
		else
		{
			printk(KERN_INFO "virgo_workqueue_handler(): kingcobra_in_userspace=0, before invoking kingcobra_servicerequest_kernelspace()\n");
			if(vwqrq != NULL)
				kingcobra_servicerequest_kernelspace(vwqrq->data);
			printk(KERN_INFO "virgo_workqueue_handler(): after invoking kingcobra_servicerequest_kernelspace()\n");
		}
	}
}


struct virgo_request* virgo_request_queue;

static int __init virgoqueue_init();
void push_request(struct virgo_request* req);
struct virgo_request* pop_request();
static void __exit virgoqueue_exit();
                                      
#endif 
