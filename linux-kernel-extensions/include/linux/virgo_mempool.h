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
Copyright(C):
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Independent Open Source Developer, Researcher and Consultant
Ph: 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

/* 
	VIRGO Memory Pooling related datastructures and driver ops
*/

#ifndef _VIRGO_MEMPOOL_H_
#define _VIRGO_MEMPOOL_H_

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

struct hostport
{
        char* hostip;
        int port;
};

struct virgo_address
{
        int node_id;
        struct hostport* hstprt;
        void* addr;
};

struct virgo_addr_transtable
{
        int node_id;
        struct hostport* hstprt;
        void* addr;
};

struct virgo_mempool_args
{
	char* mempool_cmd;
	char* mempool_args[3];
};

struct virgo_addr_transtable vtable[3000];

struct hostport* get_least_loaded_hostport_from_cloud_mempool();
char* get_host_from_cloud_Loadtrack_mempool();
char* get_host_from_cloud_PRG_mempool();
char* int_to_str(int);
char* addr_to_str(char*);

typedef void* (*FPTR)(void *args);

FPTR toFuncPtr(char*);
struct virgo_mempool_args* parse_virgomempool_command(char* mempoolFunction);

int virgocloudexec_mempool_create(void);
int virgocloudexec_mempool_recvfrom(struct socket*);
int virgocloudexec_mempool_sendto(struct socket*);

int virgo_cloudexec_mempool_service(void* args);
void do_virgocloudexec_init(void);

extern void* virgo_cloud_malloc_kernelspace(void* args);
extern void* virgo_cloud_free_kernelspace(void* args);
extern void* virgo_cloud_get_kernelspace(void* args);
extern void* virgo_cloud_set_kernelspace(void* args);

struct virgo_mempool_ops_t {
	int (*virgo_mempool_create)(void);
	int (*virgo_mempool_recvfrom)(struct socket*);
	int (*virgo_mempool_sendto)(struct socket*);
};

static struct virgo_mempool_ops_t virgo_mempool_ops = {
	.virgo_mempool_create = virgocloudexec_mempool_create,
	.virgo_mempool_recvfrom = virgocloudexec_mempool_recvfrom,
	.virgo_mempool_sendto = virgocloudexec_mempool_sendto
};

struct virgo_mempool_class_t {
	const char* m_virgo_name;
	struct module* m_virgo_owner;
	struct virgo_ops_t* m_virgo_ops;	
};

static struct virgo_mempool_class_t virgo_mempool_class = {
	.m_virgo_name = "virgo_mempool",
	.m_virgo_owner = THIS_MODULE,
	.m_virgo_ops = &virgo_mempool_ops
};

struct task_struct *task;
char* mempoolFunction;
int error;
char buffer[BUF_SIZE];
static struct socket *sock;	
static struct sockaddr_in sin;
int len=0;

/*
Multithreaded VIRGO Kernel Service - commented global declarations and moved to xxxsendto() and xxxrecvfrom() with in module 
----------------------------------------------------------------------------------------------------------------------------
static struct socket *clientsock;
static struct kvec iov;
static struct msghdr msg = { NULL, };
int buflen=BUF_SIZE;
int nr=1;
int args=0;
*/

int parameterIsExecutable=2;
struct file* file_stdout;

void print_buffer(char*);
int tokenize_list_of_ip_addrs(char* buf);
void read_virgo_config();
int kernel_space_func(void* args);
char* strip_control_M(char*);

int virgo_mempool_client_thread(void* args);


#endif /* _VIRGO_MEMPOOL_H_ */

