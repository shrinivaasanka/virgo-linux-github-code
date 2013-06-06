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
/*#include "netns.h"*/

struct hostport
{
	char* hostip;
	int port;
};

struct hostport* get_least_loaded_hostport_from_cloud()
{
	struct hostport* hopo = kmalloc(sizeof(struct hostport),GFP_KERNEL);
	hopo->hostip=kstrdup("127.0.0.1", GFP_KERNEL);
	hopo->port=10000;
	return hopo;
}

#define BUF_SIZE 3000

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
	
	int nr;
	struct kvec iov;
	struct msghdr msg = {
		.msg_flags = MSG_EOF,
	};
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

	iov.iov_base=(void*)buf;
	iov.iov_len=BUF_SIZE;	
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
	msg.msg_iov = (struct iovec *) &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	nr=1;


	strcpy(iov.iov_base, func_signature);
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgo_clone() syscall: created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "virgo_clone() syscall: connected kernel client to virgo cloudexec kernel service\n ");
	kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "virgo_clone() syscall: sent message %s \n", msg.msg_iov->iov_base);
        len  = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "virgo_clone() syscall: received message %s \n", msg.msg_iov->iov_base);
	
	return len;
}
