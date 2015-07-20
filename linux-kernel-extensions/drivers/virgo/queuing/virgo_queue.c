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

--------------------------------------------------------------------------------------------------
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Independent Open Source Developer, Researcher and Consultant
Ph: 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#include <linux/virgo_queue.h>
#include <linux/virgoqueuesvc.h>
#include <linux/virgo_config.h>
#include <linux/string.h>
#include <linux/kallsyms.h>


int queue_func(void* args)
{
	int ret=0;
	char* queueFunction=(char*)args;
	printk(KERN_INFO "queue_func(): creating kernel thread and waking up, parameterIsExecutable=%d\n", parameterIsExecutable);
        printk(KERN_INFO "queue_func(): VIRGO cloudexec is used as KingCobra service, invoking push_request() in kernelspace for data: %s\n",queueFunction);
	struct virgo_request *vrq=kmalloc(sizeof(struct virgo_request),GFP_KERNEL);
	vrq->data=kstrdup(queueFunction,GFP_KERNEL);	
	vrq->next=NULL;
	push_request(vrq);
	return 1;
}

char* strip_control_M(char* str)
{
	char* dupstr=kstrdup(str, GFP_KERNEL);
	char* newstr=strsep(&dupstr, "\r\n ");
	return newstr;
}

int kernel_space_func(void* args)
{
	printk(KERN_INFO "kernel_space_func(): parameterIsExecutable=2; executing function in kernel address space\n");
	return 0;
}

void virgoqueue_read_virgo_config()
{
	/* virgo_cloud.conf contains a string of comma separated list of IP addresses in the virgo cloud .Read and strtok() it. */

	loff_t bytesread=0;
	loff_t pos=0;
	mm_segment_t fs;

	/*
	 * It is redundant to use kallsyms_lookup for exported symbols for virgo cloud initialization. 
	 * kallsyms_lookup is for non-exported symbols.
	 * 
	 * - Ka.Shrinivaasan 10 July 2013
	 *

	virgoqueue_node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("virgoqueue_node_ip_addrs_in_cloud");
	virgoqueue_num_cloud_nodes=kallsyms_lookup_name("virgoqueue_num_cloud_nodes");

	printk(KERN_INFO "virgo kernel service: virgoqueue_read_virgo_config(): virgo_cloud config being read... \n");
	printk(KERN_INFO "virgo kernel service: virgoqueue_read_virgo_config(): virgoqueue_num_cloud_nodes=%d #### virgoqueue_node_ip_addrs_in_cloud=%s\n", virgoqueue_num_cloud_nodes,virgoqueue_node_ip_addrs_in_cloud);
	*/

	fs=get_fs();
	set_fs(get_ds());
	struct file* f=NULL;
	f=filp_open("/etc/virgo_cloud.conf", O_RDONLY, 0);

	char buf[256];
	int i=0;

	int k=0;
	for(k=0;k<256;k++)
		buf[k]=0;

	for(k=0; k < virgoqueue_num_cloud_nodes; k++)	
		printk(KERN_INFO "virgo kernel service: virgoqueue_read_virgo_config(): before reading virgo_cloud.conf - virgo_cloud ip address - %d: %s\n", k+1, virgoqueue_node_ip_addrs_in_cloud[k]);

	printk(KERN_INFO "virgoqueue_read_virgo_config(): virgo_cloud config file being read \n");


	if(f !=NULL)
	{
		/*f->f_op->read(f, buf, sizeof(buf), &f->f_pos);*/
		bytesread=vfs_read(f, buf, 256, &pos);
		/*strcpy(virgoqueue_node_ip_addrs_in_cloud[i],buf);*/
		printk(KERN_INFO " virgo_cloud config file string of comma separated IPs : %s \n",buf);
		/*printk(KERN_INFO "virgo_cloud config file line %d \n",i);*/
		pos=pos+bytesread;
	}
	/*virgoqueue_num_cloud_nodes=tokenize_list_of_ip_addrs(buf);*/
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_KERNEL);
	printk(KERN_INFO "bufdup = %s\n",bufdup);
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);
		/*printk(KERN_INFO " %s\n",token);*/
		virgoqueue_node_ip_addrs_in_cloud[i]=kstrdup(token,GFP_KERNEL);
		/*printk(KERN_INFO "virgoqueue_node_ip_addrs_in_cloud[%d] = %s\n",i,virgoqueue_node_ip_addrs_in_cloud[i]);*/
		i++;
	}
	virgoqueue_num_cloud_nodes=i;
	set_fs(fs);
	filp_close(f,NULL);	
}

/* 
Above tokenization made into a function - if needed can be used as multipurpose exported function
*/
int tokenize_list_of_ip_addrs(char* buf)
{
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_KERNEL);
	printk(KERN_INFO, "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	int i=0;
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO, "tokenize_list_of_ip_addrs(): %s\n",token);
		/*strcpy(virgoqueue_node_ip_addrs_in_cloud[i],  token);*/
		i++;
	}
	return i;
}

/*
FPTR get_function_ptr_from_str(char* queueFunction)
{
	return queue_func;
}
*/

static int __init
virgoqueue_init(void)
{
	/* native queue initialization */
	virgo_request_queue=kmalloc(VIRGO_QUEUE_SZ, GFP_KERNEL);

	/* Linux workqueue has to be differently queued-in and there need not be any explicit push and pop */
	if(use_workqueue)
	{
		printk(KERN_INFO "virgo_queue_init(): use_workqueue=1");
		if(virgo_kernel_wq==NULL)
		{
			printk(KERN_INFO "virgo_queue_init(): use_workqueue=1, virgo_kernel_wq=NULL, creating a kernel workqueue\n");
			virgo_kernel_wq = create_workqueue("virgo_kernel_workqueue");
		}
		/*
		printk(KERN_INFO "virgo_queue_init(): use_workqueue=1, enqueueing work %p to kernel workqueue\n",&virgo_work);
		queue_work(virgo_kernel_wq, &virgo_work);
		*/
	}

	printk(KERN_INFO "virgoqueue_init(): doing init() of virgocloudexec kernel module\n");
	printk(KERN_INFO "virgoqueue_init(): starting virgo cloudexec service kernel thread\n");
	
	printk(KERN_INFO "virgoqueue_init(): invoking read_virgo_config()\n");
	virgoqueue_read_virgo_config();

	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	sin.sin_port=htons(60000);

	/*stack=kmalloc(65536, GFP_KERNEL);*/
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgoqueue_init(): sock_create() returns error code: %d\n",error);

	error = kernel_bind(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	printk(KERN_INFO "virgoqueue_init(): kernel_bind() returns error code: %d\n",error);

	error = kernel_listen(sock, 2);
	printk(KERN_INFO "virgoqueue_init(): kernel_listen() returns error code: %d\n", error);

	/*
	char *kcobrabuf=kmalloc(256, GFP_KERNEL);
	strcpy(kcobrabuf,"virgoqueue_init() example initial message pushed to virgo queue which is popped by KingCobra\n");
	queue_func((void*)kcobrabuf);
	printk(KERN_INFO "virgoqueue_init(): example message pushed to virgo queue which is popped by KingCobra\n");
	*/

	virgoqueue_cloudexec_service(NULL);

	/*
	file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
	fd_install(1,file_stdout);
	fd_install(2,file_stdout);
	*/
	return 0;
}
EXPORT_SYMBOL(virgoqueue_init);

int virgoqueue_create(void)
{
	/*
	Blocking mode works in this commit again. No changes were made in virgo_clone() or driver code. 
	Hence making it a blocking socket. Root cause for this weird behaviour remains unknown.
	-Ka.Shrinivaasan
	*/
	
	/* 
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/
	struct socket *clientsock;

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
	if(error==-EAGAIN)
		printk(KERN_INFO "kernel_accept() returns -EAGAIN\n");
	printk(KERN_INFO "virgoqueue_create(): kernel_accept() returns error code: %d\n",error);
	printk(KERN_INFO "virgoqueue_create(): kernel_accept() clientsock: %u\n",clientsock);
	return clientsock;
}
EXPORT_SYMBOL(virgoqueue_create);

int virgoqueue_recvfrom(struct socket* clsock)
{
	/*
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/
	char* queueFunction;
	struct socket *clientsock=clsock;
	struct iovec iov;
	struct msghdr msg = { NULL, };
	int buflen=BUF_SIZE;
	void *args=NULL;
	int nr=1;

	struct task_struct *task;
	int error;
	char buffer[BUF_SIZE];
	char *client_ip_str;
	int len=0;
	int opt=1;

	/*	
		do kernel_recvmsg() to get the function data to be executed on a thread
	*/
	if(clientsock != NULL )
	{
		printk(KERN_INFO "virgoqueue_recvfrom(): before kernel_recvmsg()\n");
		memset(buffer, 0, BUF_SIZE);
		iov.iov_base=(void*)buffer;
		iov.iov_len=BUF_SIZE;	
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
#ifdef LINUX_KERNEL_4_x_x
                msg.msg_iter.iov = &iov;
#else
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
#endif
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags=MSG_NOSIGNAL;

		client_ip_str=kmalloc(BUF_SIZE,GFP_KERNEL);
                struct sockaddr_in* ipaddr=(struct sockaddr_in*)clientsock;
                long ipaddr_int = ntohl(ipaddr->sin_addr.s_addr);
                /*inet_ntop(AF_INET, &ipaddr_int, client_ip_str, BUF_SIZE);*/
                sprintf(client_ip_str,"%x",ipaddr_int);
                printk(KERN_INFO "virgoqueue_cpupool_recvfrom(): client_ip_str = %s\n",client_ip_str);
                client_ip_str=kstrdup(strcat(client_ip_str,"#"),GFP_KERNEL);
                printk(KERN_INFO "virgoqueue_cpupool_recvfrom(): client_ip_str with # appended = %s\n",client_ip_str);
                char* request_header=kmalloc(BUF_SIZE,GFP_KERNEL);
                sprintf(request_header,"REQUEST#");
                request_header=kstrdup(strcat(request_header,client_ip_str),GFP_KERNEL);
                char* logicaltimestamp=generate_logical_timestamp();
                request_header=kstrdup(strcat(request_header,logicaltimestamp),GFP_KERNEL);
		printk(KERN_INFO "virgoqueue_recvfrom(): after appending logical timestamp, request_header=%s\n",request_header);
		printk(KERN_INFO "virgoqueue_recvfrom(); clientsocket state = %d\n",clientsock->state);
                /*
		kernel_setsockopt(clientsock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
		kernel_setsockopt(clientsock, SOL_TCP, TCP_NODELAY, (char*)opt, sizeof(opt));
                */

		len  = kernel_recvmsg(clientsock, &msg, &iov, 1, buflen, msg.msg_flags);

		printk(KERN_INFO "virgoqueue_recvfrom(): kernel_recvmsg() returns len: %d\n",len);
		/*
			parse the message and invoke kthread_create()
			do kernel_sendmsg() with the results
		*/
		queueFunction = strip_control_M(kstrdup(buffer,GFP_KERNEL));

                queueFunction = kstrdup(strcat(request_header,queueFunction),GFP_KERNEL);
                printk(KERN_INFO "virgoqueue_recvfrom(): use_as_kingcobra_service=1, queueFunction with prepended request header and client ip=%s\n",queueFunction);
		
		printk(KERN_INFO "virgoqueue_recvfrom(): kernel_recvmsg() returns in recv buffer: %s\n", buffer);
		print_buffer(buffer);
		le32_to_cpus(buffer);
		printk(KERN_INFO "virgoqueue_recvfrom(): kernel_recvmsg() le32 to cpu %s\n", buffer);
		printk(KERN_INFO "virgoqueue_recvfrom(): queueFunction : %s \n", queueFunction);
		args=(void*)queueFunction;

		/* 
			Invoking queue_func() directly instead of a kernel thread as queue_func() itself
			spawns a kernel thread 
		*/
		queue_func(queueFunction);

		/*
		task=kthread_create(clone_func, (void*)args, "clone_func thread");
		int woken_up=wake_up_process(task);
		printk(KERN_INFO "virgoqueue_recvfrom(): clone thread woken_up : %d\n",woken_up);
		task=kthread_create(clone_func, (void*)args, "cloudclonethread");
		*/
		strcpy(buffer,"cloudclonethread executed");
	}
	return 0;
}
EXPORT_SYMBOL(virgoqueue_recvfrom);

void print_buffer(char* buffer)
{
	printk(KERN_INFO "print_buffer(): ");
	int i=0;
	for(i=0; i < sizeof(buffer); i++)
		printk(KERN_INFO "%c", buffer[i]);
	printk(KERN_INFO "\n");
}

int virgoqueue_sendto(struct socket* clsock)
{
	/*
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/

	struct socket *clientsock=clsock;
	struct iovec iov;
	struct msghdr msg = { NULL, };
	int buflen=BUF_SIZE;
	void *args=NULL;
	int nr=1;

	struct task_struct *task;
	int error;
	char buffer[BUF_SIZE];
	int len=0;

	/*
	printk(KERN_INFO "virgoqueue_sendto(): clientsock: %u\n",clientsock);
	*/
	if(clientsock != NULL)
	{
		strcpy(buffer,"virgo_cloudexec_sendto(): cloudclonethread executed for clone_func(), sending message to virgo_clone() remote syscall client\n");
		/*iov.iov_base=(void*)buffer;*/	
		memset(buffer, 0, BUF_SIZE);
		iov.iov_base=buffer;	
		iov.iov_len=BUF_SIZE;
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
#ifdef LINUX_KERNEL_4_x_x
                msg.msg_iter.iov = &iov;
#else
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
#endif
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags=0;

		int ret;
		printk(KERN_INFO "virgoqueue_sendto(): before kernel_sendmsg() for send buffer: %s\n", buffer);
		ret = kernel_sendmsg(clientsock, &msg, &iov, 1, buflen);
		/*len  = kernel_recvmsg(clientsock, &msg, &iov, 1, buflen, msg.msg_flags);*/
		/*ret = kernel_sendmsg(clientsock, &msg, &iov, nr, buflen);*/
		printk(KERN_INFO "virgoqueue_sendto(): kernel_sendmsg() returns ret: %d\n",ret);
		kernel_sock_shutdown(clientsock,SOCK_WAKE_URG);
		printk(KERN_INFO "virgoqueue_sendto(): Shut down Kernel Side Client Socket with SOCK_WAKE_URG after sendmsg \n");
		sock_release(clientsock);
		printk(KERN_INFO "virgoqueue_sendto(): sock_release invoked on client socket \n");
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

		char* queueFunction = kstrdup(iov.iov_base,GFP_KERNEL);

		int ((*queueFunction_ptr)(void*));
		queueFunction_ptr = get_function_ptr_from_str(queueFunction);
		int *args=0;
		task=kthread_create(queueFunction_ptr, (void*)args, "cloudclonethread");
		strcpy(buffer,"cloudclonethread executed");
		iov.iov_base=(void*)buf;
		iov.iov_len=BUF_SIZE;
		kernel_sendmsg(clientsock, &msg, buflen, &iov, nr);
           }
	*/
	
}
EXPORT_SYMBOL(virgoqueue_sendto);


static void __exit
virgoqueue_exit(void)
{
	printk(KERN_INFO "exiting virgocloudexec kernel module \n");
	/*filp_close(file_stdout,NULL);*/
	do_exit(1);
}
EXPORT_SYMBOL(virgoqueue_exit);

char* generate_logical_timestamp(void)
{
        char* logicaltimestamp=NULL;
        if(EventNet_timestamp==1)
        {
                return "notimplemented#";
        }
        else if(machine_timestamp==1)
        {
                logicaltimestamp=kmalloc(BUF_SIZE, GFP_KERNEL);
                /* generates a hash terminated timestamp string*/
                sprintf(logicaltimestamp,"%ld:%ld#",CURRENT_TIME,CURRENT_TIME_SEC);
                printk(KERN_INFO "generate_logical_timestamp(): machine_timestamp=1, generating timestamp for this request as %s",logicaltimestamp);
                return logicaltimestamp;

        }
        else if(other_timestamp_cloudservice==1)
        {
                return "notimplemented#";
        }
}


/*****************************************************/

/* 
	A standalone Queueing Driver implementation which either uses a kernel workqueue or a naive local queue
	that can be used for VIRGO CPU and Memory pooling Drivers requests and  
	KingCobra byzantine request servicing pub-sub model
*/


void push_request(struct virgo_request* req)
{
	if(use_workqueue)
	{
		struct virgo_workqueue_request *vwqreq=kmalloc(sizeof(struct virgo_workqueue_request),GFP_KERNEL);
		vwqreq->data=kstrdup(req->data,GFP_KERNEL);
		printk(KERN_INFO "push_request(): use_workqueue=1, enqueueing req in the kernel workqueue which will invoke handler, req->data = %s, vwqreq->work=%p, vwqreq->data = %s\n",req->data, &(vwqreq->work), vwqreq->data);
		INIT_WORK(&(vwqreq->work),virgo_workqueue_handler);
		queue_work(virgo_kernel_wq,&(vwqreq->work));
	}
	else
	{
		virgo_request_queue[queue_end].data=kstrdup(req->data,GFP_KERNEL);
		virgo_request_queue[queue_end].next=req->next;
		queue_end++;
	}
}
EXPORT_SYMBOL(push_request);

struct virgo_request* pop_request()
{
	return &virgo_request_queue[queue_front];
	queue_front++;
}
EXPORT_SYMBOL(pop_request);


MODULE_LICENSE("GPL");
module_init(virgoqueue_init);
module_exit(virgoqueue_exit);
