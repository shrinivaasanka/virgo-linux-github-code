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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan, http://ohloh.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

/* 
	VIRGO File System syscall related declarations and datastructures 
*/

#ifndef _VIRGO_FS_H_
#define _VIRGO_FS_H_

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

struct hostport
{
        char* hostip;
        int port;
};

/*
struct virgo_fs_args
{
	char* fs_cmd;
	char* fs_args[5];
	char* fsFunction;
	char* ptr;
	char* data;
};
*/

struct hostport* get_least_loaded_hostport_from_cloud_fs();
char* get_host_from_cloud_Loadtrack_fs();
char* get_host_from_cloud_PRG_fs();

char* int_to_str_vfs(int);
char* long_to_str(long n);

/*
char* addr_to_str(char*);
char* str_to_addr(char*);
char* str_to_addr2(char* straddr);

unsigned long addr_to_virgo_unique_id(struct virgo_address* vaddr);
struct virgo_address* virgo_unique_id_to_addr(unsigned long virgo_unique_id);

typedef void* (*FPTR)(struct virgo_fs_args* args);

void var_sscanf(char *str, const char* fmt, ...);

struct mutex virgo_fs_mutex;

FPTR toFuncPtr(char*);
struct virgo_fs_args* parse_virgofs_command(char* fsFunction);

int virgocloudexec_fs_create(void);
void* virgocloudexec_fs_recvfrom(struct socket*);
int virgocloudexec_fs_sendto(struct socket*, void* virgo_fs_ret);

int virgo_cloudexec_fs_service(void* args);
void do_virgocloudexec_init(void);

extern void* virgo_cloud_open_kernelspace(struct virgo_fs_args* args);
extern void* virgo_cloud_close_kernelspace(struct virgo_fs_args* args);
extern void* virgo_cloud_read_kernelspace(struct virgo_fs_args* args);
extern void* virgo_cloud_write_kernelspace(struct virgo_fs_args* args);
extern char* toKernelAddress(const char* str);

struct virgo_fs_ops_t {
	int (*virgo_fs_create)(void);
	void* (*virgo_fs_recvfrom)(struct socket*);
	int (*virgo_fs_sendto)(struct socket*,void* virgo_fs_ret);
};

static struct virgo_fs_ops_t virgo_fs_ops = {
	.virgo_fs_create = virgocloudexec_fs_create,
	.virgo_fs_recvfrom = virgocloudexec_fs_recvfrom,
	.virgo_fs_sendto = virgocloudexec_fs_sendto
};

struct virgo_fs_class_t {
	const char* m_virgo_name;
	struct module* m_virgo_owner;
	struct virgo_ops_t* m_virgo_ops;	
};

static struct virgo_fs_class_t virgo_fs_class = {
	.m_virgo_name = "virgo_fs",
	.m_virgo_owner = THIS_MODULE,
	.m_virgo_ops = &virgo_fs_ops
};

static struct socket *sock;	

int parameterIsExecutable=0;
struct file* file_stdout;

void print_buffer(char*);
int tokenize_list_of_ip_addrs(char* buf);
void read_virgo_config();
int kernel_space_func(void* args);
char* strip_control_M(char*);

int virgo_fs_client_thread(void* args);


extern int virgo_cloud_test_kernelspace(void* args);


/ File segment for virgo_fs syscalls serverside that invoke VFS kernel functions/
mm_segment_t fs;

/ Array to keep track of number of open files and generate unique VFS file descriptor for the client /
int no_of_openfiles=-1;
struct file* open_VFS_files[256];

char* toVFSString(int* data);
*/


#endif /* _VIRGO_FS_H_ */

