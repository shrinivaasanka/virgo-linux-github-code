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

#ifndef _VIRGO_H_
#define _VIRGO_H_

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

#define BUF_SIZE 500
typedef int (*FPTR)(void *args);

static int virgocloudexec_create(void);
static int virgocloudexec_recvfrom(void);
static int virgocloudexec_sendto(void);

int virgo_cloudexec_service(void* args);
void do_virgocloudexec_init(void);

extern int virgo_cloud_test_kernelspace(void* args);


/*
static struct svc_xprt_ops virgo_ops = {
	.xpo_create = virgocloudexec_create,
	.xpo_recvfrom = virgocloudexec_recvfrom,
	.xpo_sendto = virgocloudexec_sendto
};

static struct svc_xprt_class virgo_class = {
	.xcl_name = "virgo",
	.xcl_owner = THIS_MODULE,
	.xcl_ops = &virgo_ops
};
*/


struct virgo_ops_t {
	int (*virgo_create)(void);
	int (*virgo_recvfrom)(void);
	int (*virgo_sendto)(void);
};

static struct virgo_ops_t virgo_ops = {
	.virgo_create = virgocloudexec_create,
	.virgo_recvfrom = virgocloudexec_recvfrom,
	.virgo_sendto = virgocloudexec_sendto
};

struct virgo_class_t {
	const char* m_virgo_name;
	struct module* m_virgo_owner;
	struct virgo_ops_t* m_virgo_ops;	
};

static struct virgo_class_t virgo_class = {
	.m_virgo_name = "virgo",
	.m_virgo_owner = THIS_MODULE,
	.m_virgo_ops = &virgo_ops
};

struct task_struct *task;
int (*cloneFunction_ptr)(void*);
char* cloneFunction;
int error;
char buffer[BUF_SIZE];
static struct socket *sock;	
static struct sockaddr_in sin;
int len=0;

static struct socket *clientsock;
static struct kvec iov;
static struct msghdr msg = { NULL, };
int buflen=BUF_SIZE;
int nr=1;
int args=0;
int parameterIsExecutable=1;

void print_buffer(char*);
int tokenize_list_of_ip_addrs(char* buf);
void read_virgo_config();
int kernel_space_func(void* args);


/*
 * VIRGO cloudexec service kernel thread initialization
 * - Ka.Shrinivaasan 3May2013


int virgo_cloudexec_service(void* args)
{
        try_module_get(virgo_class.m_virgo_owner);
        while(1)
        {
                virgo_ops.virgo_create();
                virgo_ops.virgo_recvfrom();
                virgo_ops.virgo_sendto();
        }
}

*/

#endif /* _VIRGO_H_ */
