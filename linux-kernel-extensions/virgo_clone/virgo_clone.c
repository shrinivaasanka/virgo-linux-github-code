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
#include <linux/socket.h>

/*
#include "netns.h"
*/

struct hostport
{
	char* hostip;
	int port;
};

#define BUF_SIZE 3000

int virgocpupooling_num_cloud_nodes_client;

char* virgocpupooling_node_ip_addrs_in_client[3000];


char* get_host_from_cloud_Loadtrack();
char* get_host_from_cloud_PRG();
void virgocpupooling_read_virgo_config_client();

struct hostport* get_least_loaded_hostport_from_cloud()
{
	/*
	Either a loadtracking algorithm or a pseudorandom generator based loadbalancing algorithm is invoked to
	get the host ip for next virgo_clone() function kernel thread execution
	*/

	/*char *LBAlgorithm = "Loadtrack";*/
	char *LBAlgorithm = "PRG";
	struct hostport* hopo = kmalloc(sizeof(struct hostport),GFP_KERNEL);
	if(strcmp(LBAlgorithm, "Loadtrack")==0)
	{
		char* cloud_host = get_host_from_cloud_Loadtrack();
		hopo->hostip=kstrdup(cloud_host, GFP_KERNEL);
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_Loadtrack() returns host ip: %s \n",hopo->hostip);
		hopo->port=10000;
	}
	else if(strcmp(LBAlgorithm, "PRG")==0)
	{
		char* cloud_host = get_host_from_cloud_PRG();
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_PRG() - cloud_host(before kstrdup): %s \n",cloud_host);
		hopo->hostip=kstrdup(cloud_host, GFP_KERNEL);
		printk(KERN_INFO "get_least_loaded_hostport_from_cloud(): get_host_from_cloud_PRG() returns host ip: %s \n",hopo->hostip);
		hopo->port=10000;
	}
	return hopo;
}

/* 
 Loadtracking algorithm for  nodes in the cloud
*/

char* get_host_from_cloud_Loadtrack()
{
	return NULL;
}

/*
Pseudorandom number generator based algorithm to distribute virgo_clone() requests amongst cloud nodes
*/

char* get_host_from_cloud_PRG()
{
	unsigned int rand_int = get_random_int();
	/* 
	maps a pseudo random integer in range 0 to 2^32-1 to 0 to num_of_cloud_nodes 
	- Ka.Shrinivaasan 12 July 2013

	unsigned int rand_host_id = (virgocpupooling_num_cloud_nodes_client) * rand_int / (65536-1);
	*/

	/*
	Instead of range mapping, rand_int (mod) virgocpupooling_num_cloud_nodes_client is also sufficient
	- Ka.Shrinivaasan 12 July 2013
	*/
	unsigned int rand_host_id = rand_int % virgocpupooling_num_cloud_nodes_client;

	printk(KERN_INFO "get_host_from_cloud_PRG() - get_random_int() returned %u \n",rand_int);
	printk(KERN_INFO "get_host_from_cloud_PRG() range mapping for %d cloud nodes(virgocpupooling_num_cloud_nodes_client) returns random integer %d, host ip(nodes_ip_addrs_in_cloud): %s \n",virgocpupooling_num_cloud_nodes_client,rand_host_id, virgocpupooling_node_ip_addrs_in_client[rand_host_id]);
	return virgocpupooling_node_ip_addrs_in_client[rand_host_id];	
	
}


asmlinkage long sys_virgo_clone(char* func_signature, void *child_stack, int flags, void *arg)
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

	virgocpupooling_read_virgo_config_client();	
	int nr;
	struct iovec iov;
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
        char buf[BUF_SIZE];

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

	struct hostport* leastloadedhostport = get_least_loaded_hostport_from_cloud();
	sin.sin_family=AF_INET;
	in4_pton(leastloadedhostport->hostip, strlen(leastloadedhostport->hostip), &sin.sin_addr.s_addr, '\0',NULL);
        sin.sin_port=htons(leastloadedhostport->port);

	iov.iov_base=buf;
	iov.iov_len=sizeof(buf);	
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
#ifdef LINUX_KERNEL_4_x_x
                msg.msg_iter.iov = &iov;
#else
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
#endif
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	nr=1;


	strcpy(iov.iov_base, func_signature);
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgo_clone() syscall: created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "virgo_clone() syscall: connected kernel client to virgo cloudexec kernel service\n ");
	kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "virgo_clone() syscall: sent message: %s \n", buf);
        len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "virgo_clone() syscall: received message: %s \n", buf);
        le32_to_cpus(buf);
	printk(KERN_INFO "virgo_clone() syscall: le32_to_cpus(buf): %s \n", buf);
	sock_release(sock);
	printk(KERN_INFO "virgo_clone() syscall: virgo_clone() client socket_release() invoked\n");
	
	return len;
}

void virgocpupooling_read_virgo_config_client()
{
	/* virgo_client.conf contains a string of comma separated list of IP addresses in the virgo cloud .Read and strtok() it. */

	loff_t bytesread=0;
	loff_t pos=0;
	mm_segment_t fs;

	/*
	 * It is redundant to use kallsyms_lookup for exported symbols for virgo cloud initialization. 
	 * kallsyms_lookup is for non-exported symbols.
	 * 
	 * - Ka.Shrinivaasan 10 July 2013
	 *

	virgocpupooling_node_ip_addrs_in_client=(char**)kallsyms_lookup_name("virgocpupooling_node_ip_addrs_in_client");
	virgocpupooling_num_cloud_nodes_client=kallsyms_lookup_name("virgocpupooling_num_cloud_nodes_client");

	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgo_client.config being read... \n");
	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgocpupooling_num_cloud_nodes_client=%d #### virgocpupooling_node_ip_addrs_in_client=%s\n", virgocpupooling_num_cloud_nodes_client,virgocpupooling_node_ip_addrs_in_client);
	*/

	fs=get_fs();
	set_fs(get_ds());
	struct file* f=NULL;
	f=filp_open("/etc/virgo_client.conf", O_RDONLY, 0);

	char buf[256];
	int i=0;

	int k=0;
	for(k=0;k<256;k++)
		buf[k]=0;

	for(k=0; k < virgocpupooling_num_cloud_nodes_client; k++)	
		printk(KERN_INFO "virgo kernel service: read_virgo_config(): before reading virgo_client.conf - virgo_cloud ip address - %d: %s\n", k+1, virgocpupooling_node_ip_addrs_in_client[k]);

	printk(KERN_INFO "read_virgo_config(): virgo_client.config file being read \n");


	if(f !=NULL)
	{
		/*f->f_op->read(f, buf, sizeof(buf), &f->f_pos);*/
		bytesread=vfs_read(f, buf, 256, &pos);
		/*strcpy(virgocpupooling_node_ip_addrs_in_client[i],buf);*/
		printk(KERN_INFO "do_virgo_cloud_init(): virgo_client.config file string of comma separated IPs : %s \n",buf);
		/*printk(KERN_INFO "do_virgo_cloud_init(): virgo_client.config file line %d \n",i);*/
		pos=pos+bytesread;
	}
	/*virgocpupooling_num_cloud_nodes_client=tokenize_list_of_ip_addrs(buf);*/
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): %s\n",token);
		virgocpupooling_node_ip_addrs_in_client[i]=kstrdup(token,GFP_ATOMIC);
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): virgocpupooling_node_ip_addrs_in_client[%d] = %s\n",i,virgocpupooling_node_ip_addrs_in_client[i]);
		i++;
	}
	virgocpupooling_num_cloud_nodes_client=i;
	set_fs(fs);
	filp_close(f,NULL);	
}

/* 
Above tokenization made into a function - if needed can be used as multipurpose exported function
int tokenize_list_of_ip_addrs(char* buf)
{
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO, "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	int i=0;
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO, "tokenize_list_of_ip_addrs(): %s\n",token);
		/strcpy(virgocpupooling_node_ip_addrs_in_client[i],  token);/
		i++;
	}
	return i;
}
*/


