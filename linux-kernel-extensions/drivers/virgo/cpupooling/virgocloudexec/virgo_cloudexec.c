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

#include <linux/virgo.h>
#include <linux/virgocloudexecsvc.h>
#include <linux/string.h>

/*
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


#include <linux/sunrpc/types.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sunrpc/xdr.h>
#include <linux/sunrpc/msg_prot.h>
#include <linux/sunrpc/svcsock.h>
#include <linux/sunrpc/stats.h>
#include <linux/sunrpc/xprt.h>
//#include "sunrpc.h"//
#include <linux/sunrpc/xprt.h>
//#include "netns.h"//

#define BUF_SIZE 500
typedef int (*FPTR)(void *args);

static int virgocloudexec_create(void);
static int virgocloudexec_recvfrom(void);
static int virgocloudexec_sendto(void);

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



struct task_struct *task;
int (*cloneFunction_ptr)(void*);
char* cloneFunction;
int error;
char buffer[BUF_SIZE];
struct socket *sock;	
struct sockaddr_in sin;
int len=0;
struct socket *clientsock;
struct kvec iov;
struct msghdr msg;
int buflen=BUF_SIZE;
int nr=0;
int args=0;
*/

int clone_func(void* args)
{
	printk(KERN_INFO "clone_func(): executing the virgo_clone() syscall function parameter in cloud \n");
	/*
	Depending on scheduling priority either this or other message in virgocloudexec_sendto() will be sent to
	virgo_clone() remote syscall
	*/
	strcpy(buffer,"clone_func(): cloudclonethread executed for clone_func(), sending message to virgo_clone() remote syscall client\n");
	return 1;
}


FPTR get_function_ptr_from_str(char* cloneFunction)
{
	return clone_func;
}

static int __init
virgocloudexec_init(void)
{
	printk(KERN_INFO "virgocloudexec_init(): doing init() of virgocloudexec kernel module\n");
	printk(KERN_INFO "virgocloudexec_init(): starting virgo cloudexec service kernel thread\n");
	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	sin.sin_port=htons(10000);

	/*stack=kmalloc(65536, GFP_KERNEL);*/
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgocloudexec_init(): sock_create() returns error code: %d\n",error);

	error = kernel_bind(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	printk(KERN_INFO "virgocloudexec_init(): kernel_bind() returns error code: %d\n",error);

	error = kernel_listen(sock, 2);
	printk(KERN_INFO "virgocloudexec_init(): kernel_listen() returns error code: %d\n", error);

	virgo_cloudexec_service(NULL);
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_init);

static int virgocloudexec_create(void)
{
	/*
	Blocking mode works in this commit again. No changes were made in virgo_clone() or driver code. 
	Hence making it a blocking socket. Root cause for this weird behaviour remains unknown.
	-Ka.Shrinivaasan
	*/
	 
	clientsock=NULL;
	error = kernel_accept(sock, &clientsock, 0);
	
	/*
	Blocking mode was working and kernel thread was listening and accepting connections without blocking the bootup till previous commit, 
	but suddenly it started to block on startup. Reason unknown (could be anything from hardware microcode update to external 
	causes viz., intrusion. These kind of events recur with high frequency. Needs further investigation). 
	There seems to be no error in the driver kernel service thread or syscall client.

        Making it temporarily O_NONBLOCK which seems to be quite a cleaner way despite EAGAIN to accept connections as this is always 
	in a while loop for server.

	Moreover the driver modules_install places it in /lib/modules/`uname -r`/extra which did not occur in previous commit. Origin
	again mysterious.

	-Ka.Shrinivaasan  
	error = kernel_accept(sock, &clientsock, O_NONBLOCK);
	*/
	/*
	if(error==-EAGAIN)
		printk(KERN_INFO "kernel_accept() returns -EAGAIN\n");
	printk(KERN_INFO "virgocloudexec_create(): kernel_accept() returns error code: %d\n",error);
	printk(KERN_INFO "virgocloudexec_create(): kernel_accept() clientsock: %u\n",clientsock);
	*/
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_create);

static int virgocloudexec_recvfrom(void)
{
	/*	
		do kernel_recvmsg() to get the function data to be executed on a thread
	*/
	/*
	printk(KERN_INFO "virgocloudexec_recvfrom(): clientsock: %u\n",clientsock);
	*/
	if(clientsock != NULL )
	{
		printk(KERN_INFO "virgocloudexec_recvfrom(): before kernel_recvmsg()\n");
		memset(buffer, 0, sizeof(buffer));
		iov.iov_base=(void*)buffer;
		iov.iov_len=sizeof(buffer);	
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		/*msg.msg_flags=0;*/
		msg.msg_flags=MSG_NOSIGNAL;

		/*
		len  = kernel_recvmsg(clientsock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
		*/
		len  = kernel_recvmsg(clientsock, &msg, &iov, 1, buflen, msg.msg_flags);
		printk(KERN_INFO "virgocloudexec_recvfrom(): kernel_recvmsg() returns len: %d\n",len);
		/*
			parse the message and invoke kthread_create()
			do kernel_sendmsg() with the results
		*/
		cloneFunction = kstrdup(buffer,GFP_ATOMIC);
		printk(KERN_INFO "virgocloudexec_recvfrom(): kernel_recvmsg() returns in recv buffer: %s\n", buffer);
		print_buffer(buffer);
		le32_to_cpus(buffer);
		printk(KERN_INFO "virgocloudexec_recvfrom(): kernel_recvmsg() le32 to cpu %s\n", buffer);
		printk(KERN_INFO "virgocloudexec_recvfrom(): cloneFunction : %s \n", cloneFunction);
		cloneFunction_ptr = get_function_ptr_from_str(cloneFunction);
		/*task=kthread_run(cloneFunction_ptr, (void*)args, "cloudclonethread");*/
		task=kthread_create(cloneFunction_ptr, (void*)args, "cloudclonethread");
		int woken_up=wake_up_process(task);
		printk(KERN_INFO "virgocloudexec_recvfrom(): clone thread woken_up : %d\n",woken_up);
		/*
		task=kthread_create(clone_func, (void*)args, "cloudclonethread");
		strcpy(buffer,"cloudclonethread executed");
		*/
	}
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_recvfrom);

void print_buffer(char* buffer)
{
	printk(KERN_INFO "print_buffer(): ");
	int i=0;
	for(i=0; i < sizeof(buffer); i++)
		printk(KERN_INFO "%c", buffer[i]);
	printk(KERN_INFO "\n");
}

static int virgocloudexec_sendto(void)
{
	/*
	printk(KERN_INFO "virgocloudexec_sendto(): clientsock: %u\n",clientsock);
	*/
	if(clientsock != NULL)
	{
		strcpy(buffer,"virgo_cloudexec_sendto(): cloudclonethread executed for clone_func(), sending message to virgo_clone() remote syscall client\n");
		/*iov.iov_base=(void*)buffer;*/	
		/*memset(buffer, 0, sizeof(buffer));*/
		iov.iov_base=buffer;	
		/*iov.iov_len=BUF_SIZE;*/
		iov.iov_len=sizeof(buffer);
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags=0;

		int ret;
		printk(KERN_INFO "virgocloudexec_sendto(): before kernel_sendmsg() for send buffer: %s\n", buffer);
		ret = kernel_sendmsg(clientsock, &msg, &iov, 1, buflen);
		/*len  = kernel_recvmsg(clientsock, &msg, &iov, 1, buflen, msg.msg_flags);*/
		/*ret = kernel_sendmsg(clientsock, &msg, &iov, nr, buflen);*/
		printk(KERN_INFO "virgocloudexec_sendto(): kernel_sendmsg() returns ret: %d\n",ret);
		/*
		printk(KERN_INFO "virgocloudexec_sendto(): kernel_recvmsg() returns len: %d\n",len);
		printk(KERN_INFO "virgocloudexec_sendto(): kernel_recvmsg() returns in recv buffer: %s\n", buffer);
		*/
		kernel_sock_shutdown(clientsock,SOCK_WAKE_URG);
		printk(KERN_INFO "virgocloudexec_sendto(): Shut down Kernel Side Client Socket with SOCK_WAKE_URG after sendmsg \n");
		sock_release(clientsock);
		printk(KERN_INFO "virgocloudexec_sendto(): sock_release invoked on client socket \n");
	}
	return 0;

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
EXPORT_SYMBOL(virgocloudexec_sendto);


static void __exit
virgocloudexec_exit(void)
{
	printk(KERN_INFO "exiting virgocloudexec kernel module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgocloudexec_exit);


MODULE_LICENSE("GPL");
module_init(virgocloudexec_init);
module_exit(virgocloudexec_exit);
