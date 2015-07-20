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

---------------------------------------------------------------------------------------------------------
Copyright (C):
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Ph: 9789346927, 9003082186, 9791165980
Krishna iResearch Open Source Products Profiles:
http://sourceforge.net/users/ka_shrinivaasan, https://www.openhub.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
ZODIAC DATASOFT: https://github.com/shrinivaasanka/ZodiacDatasoft
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
---------------------------------------------------------------------------------------------------------

*****************************************************************************************/

/* 
	VIRGO File System related datastructures and driver ops
*/

#ifndef _VIRGO_EVENTNET_H_
#define _VIRGO_EVENTNET_H_

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

#include <linux/sunrpc/types.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sunrpc/xdr.h>
#include <linux/sunrpc/msg_prot.h>
#include <linux/sunrpc/svcsock.h>
#include <linux/sunrpc/stats.h>
#include <linux/sunrpc/xprt.h>
#include <linux/sunrpc/xprt.h>

#define BUF_SIZE 500

#define LINUX_KERNEL_4_x_x

struct hostport
{
        char* hostip;
        int port;
};

struct virgo_eventnet_args
{
	char* event_message_type;
	char* event_id;
	/*
	Based on event_message_type(0 or 1) the args are either :
	- 0) Vertex messages : intraevent partakers arg0, arg1, arg2 (or)
	- 1) Edge messages : interevent edge vertices arg0 and arg1
	*/
	char* eventid_args[3];
	char* ptr;
	char* data;
};


struct hostport* get_least_loaded_hostport_from_cloud_eventnet();
char* get_host_from_cloud_Loadtrack_eventnet();
char* get_host_from_cloud_PRG_eventnet();
char* int_to_str(int);
char* addr_to_str(char*);
char* str_to_addr(char*);
char* str_to_addr2(char* straddr);

unsigned long addr_to_virgo_unique_id(struct virgo_address* vaddr);
struct virgo_address* virgo_unique_id_to_addr(unsigned long virgo_unique_id);

typedef void* (*FPTR)(struct virgo_eventnet_args* args);

void var_sscanf(char *str, const char* fmt, ...);

struct mutex virgo_eventnet_mutex;

struct file* verticesf=NULL;
struct file* edgesf=NULL;
loff_t pos = 0;
size_t cnt = 0;


FPTR toFuncPtr(char*);
struct virgo_eventnet_args* parse_virgoeventnet_command(char* eventnetFunction);

int virgocloudexec_eventnet_create(void);
void* virgocloudexec_eventnet_recvfrom(struct socket*);
int virgocloudexec_eventnet_sendto(struct socket*, void* virgo_eventnet_ret);

int virgo_cloudexec_eventnet_service(void* args);
void do_virgocloudexec_init(void);

void virgo_cloud_eventnet_edgemsg_kernelspace(struct virgo_eventnet_args* args);
void virgo_cloud_eventnet_vertexmsg_kernelspace(struct virgo_eventnet_args* args);

extern char* toKernelAddress(const char* str);

struct virgo_eventnet_ops_t {
	int (*virgo_eventnet_create)(void);
	void* (*virgo_eventnet_recvfrom)(struct socket*);
	int (*virgo_eventnet_sendto)(struct socket*,void* virgo_fs_ret);
};

static struct virgo_eventnet_ops_t virgo_eventnet_ops = {
	.virgo_eventnet_create = virgocloudexec_eventnet_create,
	.virgo_eventnet_recvfrom = virgocloudexec_eventnet_recvfrom,
	.virgo_eventnet_sendto = virgocloudexec_eventnet_sendto
};

struct virgo_eventnet_class_t {
	const char* m_virgo_name;
	struct module* m_virgo_owner;
	struct virgo_eventnet_ops_t* m_virgo_ops;	
};

static struct virgo_eventnet_class_t virgo_eventnet_class = {
	.m_virgo_name = "virgo_fs",
	.m_virgo_owner = THIS_MODULE,
	.m_virgo_ops = &virgo_eventnet_ops
};

static struct socket *sock;	

int parameterIsExecutable=2;
struct file* file_stdout;

void print_buffer(char*);
int tokenize_list_of_ip_addrs(char* buf);
void virgoeventnet_read_virgo_config();
int kernel_space_func(void* args);
char* strip_control_M(char*);

int virgo_eventnet_client_thread(void* args);


extern int virgo_cloud_test_kernelspace(void* args);


/* File segment for virgo_fs syscalls serverside that invoke VFS kernel functions*/
mm_segment_t fs;

/* Array to keep track of number of open files and generate unique VFS file descriptor for the client */
int no_of_openfiles=-1;
struct file* open_VFS_files[256];

char* toVFSString(int* data);


#endif /* _VIRGO_EVENTNET_H_ */

