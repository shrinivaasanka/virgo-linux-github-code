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

#define LINUX_KERNEL_4_x_x

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
#include <linux/time.h>

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
	/*
	allocation unique id to uniquely identify all chunks  for that cloud allocation
	*/
	int cloud_alloc_id;
	/*
	For future use - reference count for this address
	*/
	int refcount;
};

struct virgo_addr_transtable
{

	/*
	address table of size 3000 for maximum of 3000 cloud nodes
	*/
	struct virgo_address vtable[3000];


	/*
	for future use - if some search algorithm is needed for tree representation of transtable 
	fragments distributed geographically. Each fragment is for maximum of 3000 cloud nodes.
	*/
	struct virgo_addr_transtable* vtable_left;
	struct virgo_addr_transtable* vtable_right;

	/*
	for future use - Set to 1 if virgo_addr_transtable fragment is persisted in disk
	*/
	int fragment_is_disk_persisted;

	/*
	Mutex to synchronize access to this address table fragment
	*/
	struct mutex vtable_fragment_mutex;
};

struct virgo_mempool_args
{
	char* mempool_cmd;
	char* mempool_args[3];
	char* mempoolFunction;
	char* ptr;
	char* data;
};


struct hostport* get_least_loaded_hostport_from_cloud_mempool();
char* get_host_from_cloud_Loadtrack_mempool();
char* get_host_from_cloud_PRG_mempool();
char* int_to_str(int);
char* addr_to_str(char*);
char* str_to_addr(char*);
char* str_to_addr2(char* straddr);

unsigned long addr_to_virgo_unique_id(struct virgo_address* vaddr);
struct virgo_address* virgo_unique_id_to_addr(unsigned long virgo_unique_id);

typedef void* (*FPTR)(struct virgo_mempool_args* args);

void var_sscanf(char *str, const char* fmt, ...);

struct mutex virgo_mempool_mutex;

FPTR toFuncPtr(char*);
struct virgo_mempool_args* parse_virgomempool_command(char* mempoolFunction);
/*struct virgo_mempool_args* parse_virgomempool_command(void* args);*/

int virgocloudexec_mempool_create(void);
void* virgocloudexec_mempool_recvfrom(struct socket*);
int virgocloudexec_mempool_sendto(struct socket*, void* virgo_mempool_ret);

int virgo_cloudexec_mempool_service(void* args);
void do_virgocloudexec_init(void);

extern void* virgo_cloud_malloc_kernelspace(struct virgo_mempool_args* args);
extern void* virgo_cloud_free_kernelspace(struct virgo_mempool_args* args);
extern void* virgo_cloud_get_kernelspace(struct virgo_mempool_args* args);
extern void* virgo_cloud_set_kernelspace(struct virgo_mempool_args* args);
extern char* toKernelAddress(const char* str);

struct virgo_mempool_ops_t {
	int (*virgo_mempool_create)(void);
	void* (*virgo_mempool_recvfrom)(struct socket*);
	int (*virgo_mempool_sendto)(struct socket*,void* virgo_mempool_ret);
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

/*
struct task_struct *task;
char* mempoolFunction;
int error;
char buffer[BUF_SIZE];
*/

struct socket *sock;	

/*
static struct sockaddr_in sin;
int len=0;
*/

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
void virgomemorypooling_read_virgo_config();
int kernel_space_func(void* args);
char* strip_control_M(char*);

int virgo_mempool_client_thread(void* args);
char* toAddressString(char* ptr);

char* generate_logical_timestamp(void);

struct virgo_addr_transtable vtranstable;
int alloc_id=1;
int next_vtable_entry=0;

extern int virgo_cloud_test_kernelspace(void* args);

extern void push_request(struct virgo_request* vrq);


/*
New boolean flag added for using VIRGO cloud mempool for KingCobra. If set to 1, VIRGO cloudexec service
in mempooling driver is invoked in kernelspace.
*/

int use_as_kingcobra_service=0;

/*
Following boolean flags have been added for various logical timestamp generation schemes to be prepended to the request header so that
no two requests in the VIRGO-KingCobra cloud have the same timestamps:

1) EventNet_timestamp is not implemented and for future use with EventNet implementation in AsFer depending on its feasibility.
2) machine_timestamp is the timestamp generated by kernel macros in the request recipient machine
3) other_timestamp_cloudservice is for any other cloud based timestamp services like NTP etc., and not implemented
*/

int EventNet_timestamp=0;
int machine_timestamp=1;
int other_timestamp_cloudservice=0;


#endif /* _VIRGO_MEMPOOL_H_ */

