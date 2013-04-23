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

#define BUF_SIZE 500

int clone_func(void* args)
{
	return 1;
}


int (*get_function_ptr_from_str(void* args))(char* cloneFunction)
{
	return clone_func;
}

static int __init
virgocloudexec_init(void)
{
	struct task_struct *task;
	int error;
	char buffer[3000];
	struct net *net;
	int family=PF_INET;
	int type=SOCK_STREAM;
	int protocol=IPPROTO_TCP;
	struct socket *sock;	
	struct sockaddr_in sin;
	int len;
	struct socket *clientsock;
	struct kvec iov;
	struct msghdr msg = {
		.msg_flags = MSG_DONTWAIT,
	};
	int buflen;
	int nr;
	char* stack;

	/*
	union {
                struct cmsghdr  hdr;
                long            all[3000];
        } buffer;
        struct cmsghdr *cmh = &buffer.hdr;
	*/

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	sin.sin_port=htons(60000);

	stack=kmalloc(65536, GFP_KERNEL);
	iov.iov_base=(void*)buffer;
	iov.iov_len=3000;	
	error = sock_create(family, type, protocol, &sock);
	kernel_bind(sock, (struct sockaddr*)&sin,len);
	kernel_listen(sock,64);

	while(1)
	{
		error = kernel_accept(sock, clientsock, O_NONBLOCK);
		/*	
			do kernel_recvmsg() to get the function data to be executed on a thread
		*/
		len  = kernel_recvmsg(clientsock, &msg, buflen, &iov, nr, msg.msg_flags);
		/*
			parse the message and invoke kthread_create()
			do kernel_sendmsg() with the results
		*/
		char* cloneFunction = kstrdup(iov.iov_base,GFP_KERNEL);
		int (*cloneFunction_ptr)(void*);
		cloneFunction_ptr = get_function_ptr_from_str(cloneFunction);
		int args=0;
		task=kthread_create(cloneFunction_ptr, (void*)args, "cloudclonethread");
		strcpy(buffer,"cloudclonethread executed");
		iov.iov_base=(void*)buffer;
		iov.iov_len=25;
		kernel_sendmsg(clientsock, &msg, buflen, &iov, nr);
	}

	/*
	   struct task_struct *task;
	   int error;
           struct addrinfo hints;
	   struct socket* sock;
	   struct socket* client_sock;
           struct addrinfo *result, *rp;
           int sfd, s;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[BUF_SIZE];
           struct kvec iov;
	   struct msghdr msg = {
			.msg_flags = MSG_DONTWAIT,
	   };

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    / Allow IPv4 or IPv6 /
           hints.ai_socktype = SOCK_STREAM; / Datagram socket /
           hints.ai_flags = AI_PASSIVE;    / For wildcard IP address /
           hints.ai_protocol = 0;          / Any protocol /
           hints.ai_canonname = NULL;
           hints.ai_addr = NULL;
           hints.ai_next = NULL;

	   char* cloud_clone_port=60000;

	   stack=kmalloc(65536, GFP_KERNEL);
	   iov.iov_base=(void*)buf;
	   iov.iov_len=BUF_SIZE;	
           s = getaddrinfo(NULL, cloud_clone_port, &hints, &result);

           sock_create(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol, sock);

           kernel_bind(sock, rp->ai_addr, rp->ai_addrlen);
	   kernel_listen(sock,64);

           freeaddrinfo(result);           / No longer needed /

           error = kernel_accept(sock, clientsock, O_NONBLOCK);

           for (;;) {
		nread  = kernel_recvmsg(clientsock, &msg, buflen, &iov, nr, msg.msg_flags);

		char* cloneFunction = kstrdup(iov.iov_base,GFP_KERNEL);

		int ((*cloneFunction_ptr)(void*));
		cloneFunction_ptr = get_function_ptr_from_str(cloneFunction);
		int *args=0;
		task=kthread_create(cloneFunction_ptr, (void*)args, "cloudclonethread");
		strcpy(buffer,"cloudclonethread executed");
		iov.iov_base=(void*)buf;
		iov.iov_len=BUF_SIZE;
		kernel_sendmsg(clientsock, &msg, buflen, &iov, nr);
           }
	*/

}

static void __exit
virgocloudexec_exit(void)
{
	do_exit(1);
}


MODULE_LICENSE("GPL");
module_init(virgocloudexec_init);
module_exit(virgocloudexec_exit);
