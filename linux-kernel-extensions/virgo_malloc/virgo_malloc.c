/***************************************************************************************
VIRGO - VIRtual Generic Os - linux kernel extensions for cloud 


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
#include <linux/init.h>

#include <linux/random.h>

#include <linux/virgo_config.h>
#include <linux/virgo_mempool.h>

/*
#include "netns.h"
*/

/*
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
*/

#define BUF_SIZE 3000

#define PER_NODE_MALLOC_CHUNK_SIZE 1000

/*
extern int num_cloud_nodes;

extern char* node_ip_addrs_in_cloud[3000];
*/

/*
struct virgo_addr_transtable vtable[3000];

char* get_host_from_cloud_Loadtrack_mempool();
char* get_host_from_cloud_PRG_mempool();
char* int_to_str(int);
char* addr_to_str(char*);
*/

struct hostport* get_least_loaded_hostport_from_cloud_mempool()
{
	/*
	Either a loadtracking algorithm or a pseudorandom generator based loadbalancing algorithm is invoked to
	get the host ip for next virgo_malloc() function kernel thread execution
	*/

	/*char *LBAlgorithm = "Loadtrack";*/
	char *LBAlgorithm = "PRG";
	struct hostport* hopo = kmalloc(sizeof(struct hostport),GFP_KERNEL);
	if(strcmp(LBAlgorithm, "Loadtrack")==0)
	{
		char* cloud_host = get_host_from_cloud_Loadtrack_mempool();
		hopo->hostip=kstrdup(cloud_host, GFP_KERNEL);
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_Loadtrack_mempool() returns host ip: %s \n",hopo->hostip);
		hopo->port=10000;
	}
	else if(strcmp(LBAlgorithm, "PRG")==0)
	{
		char* cloud_host = get_host_from_cloud_PRG_mempool();
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_PRG_mempool() - cloud_host(before kstrdup): %s \n",cloud_host);
		hopo->hostip=kstrdup(cloud_host, GFP_KERNEL);
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_PRG_mempool() returns host ip: %s \n",hopo->hostip);
		hopo->port=10000;
	}
	return hopo;
}

/* 
 Loadtracking algorithm for  nodes in the cloud
*/

char* get_host_from_cloud_Loadtrack_mempool()
{
	return NULL;
}

/*
Pseudorandom number generator based algorithm to distribute virgo_malloc() requests amongst cloud nodes
*/

char* get_host_from_cloud_PRG_mempool()
{
	unsigned int rand_int = get_random_int();
	/* 
	maps a pseudo random integer in range 0 to 2^32-1 to 0 to num_of_cloud_nodes 
	- Ka.Shrinivaasan 12 July 2013

	unsigned int rand_host_id = (num_cloud_nodes) * rand_int / (65536-1);
	*/

	/*
	Instead of range mapping, rand_int (mod) num_cloud_nodes is also sufficient
	- Ka.Shrinivaasan 12 July 2013
	*/
	unsigned int rand_host_id = rand_int % num_cloud_nodes;

	printk(KERN_INFO "get_host_from_cloud_PRG_mempool() - get_random_int() returned %u \n",rand_int);
	printk(KERN_INFO "get_host_from_cloud_PRG_mempool() range mapping for %d cloud nodes(num_cloud_nodes) returns random integer %d, host ip(nodes_ip_addrs_in_cloud): %s \n",num_cloud_nodes,rand_host_id, node_ip_addrs_in_cloud[rand_host_id]);
	return node_ip_addrs_in_cloud[rand_host_id];	
	
}


asmlinkage char* sys_virgo_get(struct virgo_address* vaddr)
{
	int nr;
	struct kvec iov;
	struct msghdr msg;
	int error;
	struct socket *sock;
	struct sockaddr_in sin;
        int sfd, s, j;
        size_t len;
        ssize_t nread;
        /*char buf[BUF_SIZE];*/
	char *buf;

	int chunk_size=0;
	int sum_alloc_size=0;
	sin.sin_family=AF_INET;
	in4_pton(vaddr->hstprt->hostip, strlen(vaddr->hstprt->hostip), &sin.sin_addr.s_addr, '\0',NULL);
       	sin.sin_port=htons(vaddr->hstprt->port);

	char* virgo_get_cmd;
	virgo_get_cmd=strcat("virgo_cloud_get(",addr_to_str(vaddr->addr));
	virgo_get_cmd=strcat(virgo_get_cmd, ")");
	buf=kstrdup(virgo_get_cmd, GFP_ATOMIC);			

	iov.iov_base=buf;
	iov.iov_len=sizeof(buf);	
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
	msg.msg_iov = (struct iovec *) &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	nr=1;
	
	strcpy(iov.iov_base, buf);
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgo_get() syscall: created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "virgo_get() syscall: connected kernel client to virgo cloudexec kernel service\n ");
	kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "virgo_get() syscall: sent message: %s \n", buf);
       	len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "virgo_get() syscall: received message: %s \n", buf);

	le32_to_cpus(buf);
	printk(KERN_INFO "virgo_get() syscall: le32_to_cpus(buf): %s \n", buf);
	sock_release(sock);
	printk(KERN_INFO "virgo_get() syscall: virgo_get() client socket_release() invoked\n");
	return buf;
}


asmlinkage char* sys_virgo_set(struct virgo_address* vaddr, void* data)
{
	int nr;
	struct kvec iov;
	struct msghdr msg;
	int error;
	struct socket *sock;
	struct sockaddr_in sin;
        int sfd, s, j;
        size_t len;
        ssize_t nread;
        /*char buf[BUF_SIZE];*/
	char* buf;
	

	int chunk_size=0;
	int sum_alloc_size=0;
	sin.sin_family=AF_INET;
	in4_pton(vaddr->hstprt->hostip, strlen(vaddr->hstprt->hostip), &sin.sin_addr.s_addr, '\0',NULL);
       	sin.sin_port=htons(vaddr->hstprt->port);

	char* virgo_set_cmd;
	virgo_set_cmd=strcat("virgo_cloud_set(",addr_to_str(vaddr->addr));
	virgo_set_cmd=strcat(virgo_set_cmd,",");
	virgo_set_cmd=strcat(virgo_set_cmd, (char*)data);
	virgo_set_cmd=strcat(virgo_set_cmd, ")");
	buf=kstrdup(virgo_set_cmd, GFP_ATOMIC);			

	iov.iov_base=buf;
	iov.iov_len=sizeof(buf);	
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
	msg.msg_iov = (struct iovec *) &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	nr=1;
	
	strcpy(iov.iov_base, buf);
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgo_set() syscall: created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "virgo_set() syscall: connected kernel client to virgo cloudexec kernel service\n ");
	kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "virgo_set() syscall: sent message: %s \n", buf);
       	len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "virgo_set() syscall: received message: %s \n", buf);

	le32_to_cpus(buf);
	printk(KERN_INFO "virgo_set() syscall: le32_to_cpus(buf): %s \n", buf);
	sock_release(sock);
	printk(KERN_INFO "virgo_set() syscall: virgo_set() client socket_release() invoked\n");
	return buf;
}


asmlinkage struct virgo_address* sys_virgo_malloc(int size)
{
	/*
	int error;
	char buffer[3000];
	int family=PF_INET;
	int type=SOCK_STREAM;
	int protocol=IPPROTO_TCP;
	struct socket *sock;	
	struct sockaddr_in server;
	int len;
	struct kvec iov;
	struct msghdr msg = {
		.msg_flags = MSG_DONTWAIT,
	};
	int buflen;
	int nr;

	char* leastloadedhost = get_least_loaded_host_from_cloud();
	struct hostent* remotehost=gethostbyname(leastloadedhost);
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(60000);
	iov.iov_base=(void*)buffer;
	iov.iov_len=3000;	
	strcpy(iov.iov_base, func_signature);
	*/	

	int no_of_chunks=1;	
	int nr;
	struct kvec iov;
	/*
	struct msghdr msg = {
		.msg_flags = MSG_EOF,
	};
	*/
	struct msghdr msg;
	int error;
	struct socket *sock;
	struct sockaddr_in sin;
	/*
        struct addrinfo hints;
        struct addrinfo *result, *rp;
	*/
        int sfd, s, j;
        size_t len;
        ssize_t nread;
        /*char buf[BUF_SIZE];*/
	char *buf;
	char *malloc_cmd;

	/*
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;    / Allow IPv4 or IPv6 /
        hints.ai_socktype = SOCK_STREAM; / Datagram socket /
        hints.ai_flags = 0;
        hints.ai_protocol = 0;          / Any protocol /
	*/

	/*
	struct hostport* leastloadedhostport = get_least_loaded_hostport_from_cloud();
        s = getaddrinfo(leastloadedhostport->host, leastloadedhostport->port, &hints, &result);
	*/

	int chunk_size=0;
	int sum_alloc_size=0;
	int i=0;
	while(true)	
	{
		struct hostport* leastloadedhostport = get_least_loaded_hostport_from_cloud_mempool();
		sin.sin_family=AF_INET;
		in4_pton(leastloadedhostport->hostip, strlen(leastloadedhostport->hostip), &sin.sin_addr.s_addr, '\0',NULL);
       		sin.sin_port=htons(leastloadedhostport->port);
	
		if(sum_alloc_size + PER_NODE_MALLOC_CHUNK_SIZE <= size)
		{
			chunk_size=PER_NODE_MALLOC_CHUNK_SIZE;	
			buf=kstrdup("virgo_cloud_malloc(1000)",GFP_ATOMIC);			
		}
		else
		{
			chunk_size=size-sum_alloc_size;
			malloc_cmd=strcat("virgo_cloud_malloc(",int_to_str(chunk_size));
			malloc_cmd=strcat(malloc_cmd, ")");
			buf=kstrdup(malloc_cmd,GFP_ATOMIC);
		}

		iov.iov_base=buf;
		iov.iov_len=sizeof(buf);	
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags = 0;
		nr=1;
	
		strcpy(iov.iov_base, buf);
		error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
		printk(KERN_INFO "virgo_malloc() syscall: created client kernel socket\n");
		kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
		printk(KERN_INFO "virgo_malloc() syscall: connected kernel client to virgo cloudexec kernel service\n ");
		kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
		printk(KERN_INFO "virgo_malloc() syscall: sent message: %s \n", buf);
       		len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
		printk(KERN_INFO "virgo_malloc() syscall: received message: %s \n", buf);
	
		struct virgo_address v_addr;
		sscanf(buf,"%p",v_addr.addr);
		v_addr.node_id=i;
		v_addr.hstprt=leastloadedhostport;

		vtable[i].node_id=v_addr.node_id;
		vtable[i].addr=v_addr.addr;
		vtable[i].hstprt=leastloadedhostport;
       
		le32_to_cpus(buf);
		printk(KERN_INFO "virgo_malloc() syscall: le32_to_cpus(buf): %s \n", buf);
		sock_release(sock);
		printk(KERN_INFO "virgo_malloc() syscall: virgo_malloc() client socket_release() invoked\n");
		sum_alloc_size+=chunk_size;
		if(chunk_size < PER_NODE_MALLOC_CHUNK_SIZE)
			break;
		i++;
	}	
	return vtable[0].addr;
}

asmlinkage char* sys_virgo_free(struct virgo_address* vaddr)
{
	int nr;
	struct kvec iov;
	struct msghdr msg;
	int error;
	struct socket *sock;
	struct sockaddr_in sin;
        int sfd, s, j;
        size_t len;
        ssize_t nread;
        /*char buf[BUF_SIZE];*/
	char* buf;
	char* free_cmd;

	sin.sin_family=AF_INET;
	in4_pton(vaddr->hstprt->hostip, strlen(vaddr->hstprt->hostip), &sin.sin_addr.s_addr, '\0',NULL);
       	sin.sin_port=htons(vaddr->hstprt->port);
	
	free_cmd=strcat("virgo_cloud_free(",addr_to_str(vaddr->addr));
	free_cmd=strcat(free_cmd, ")");
	buf=kstrdup(free_cmd,GFP_ATOMIC);

	iov.iov_base=buf;
	iov.iov_len=sizeof(buf);	
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
	msg.msg_iov = (struct iovec *) &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	nr=1;
	
	strcpy(iov.iov_base, buf);
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgo_free() syscall: created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "virgo_free() syscall: connected kernel client to virgo cloudexec kernel service\n ");
	kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "virgo_free() syscall: sent message: %s \n", buf);
       	len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "virgo_free() syscall: received message: %s \n", buf);
	
	le32_to_cpus(buf);
	printk(KERN_INFO "virgo_free() syscall: le32_to_cpus(buf): %s \n", buf);
	sock_release(sock);
	printk(KERN_INFO "virgo_free() syscall: virgo_free() client socket_release() invoked\n");
	return buf;
}

char* int_to_str(int n)
{
	char* ret=(char*)kmalloc(50,GFP_ATOMIC);
	sprintf(ret,"%d",n);
	return ret;
}

char* addr_to_str(char* addr)
{
	char* ret=(char*)kmalloc(50,GFP_ATOMIC);
	sprintf(ret,"%p",addr);
	return ret;
}
