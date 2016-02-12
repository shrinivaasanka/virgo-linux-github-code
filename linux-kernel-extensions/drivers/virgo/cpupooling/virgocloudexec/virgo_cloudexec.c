/***************************************************************************************
+#-------------------------------------------------------------------------------------------------------
+#NEURONRAIN VIRGO - Cloud, Machine Learning and Queue augmented Linux Kernel Fork-off
+#This program is free software: you can redistribute it and/or modify
+#it under the terms of the GNU General Public License as published by
+#the Free Software Foundation, either version 3 of the License, or
+#(at your option) any later version.
+#This program is distributed in the hope that it will be useful,
+#but WITHOUT ANY WARRANTY; without even the implied warranty of
+#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+#GNU General Public License for more details.
+#You should have received a copy of the GNU General Public License
+#along with this program.  If not, see <http://www.gnu.org/licenses/>.
+#--------------------------------------------------------------------------------------------------------
+#Copyleft (Copyright+):
+#Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
+#Ph: 9791499106, 9003082186
+#Krishna iResearch Open Source Products Profiles:
+#http://sourceforge.net/users/ka_shrinivaasan,
+#https://github.com/shrinivaasanka,
+#https://www.openhub.net/accounts/ka_shrinivaasan
+#Personal website(research): https://sites.google.com/site/kuja27/
+#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com,
+#kashrinivaasan@live.com
+#--------------------------------------------------------------------------------------------------------
*****************************************************************************************/

#include <linux/virgo.h>
#include <linux/virgocloudexecsvc.h>
#include <linux/virgo_config.h>
#include <linux/string.h>
#include <linux/kallsyms.h>

struct virgo_request
{
        char* data;
        struct virgo_request* next;
};


/*
* The wrapper function that based on switch parameterIsExecutable (values 0,1,2) executes the binary or function data from virgo_clone
* system call in either kernel or user address-spaces
* - Ka.Shrinivaasan
*/
 
int clone_func(void* args)
{
	/*
	 * Lack of reflection kind of facilities requires map of function_names to pointers_to_functions to be executed
	 * on cloud. Function name has to be lookedup in the map to get pointer to function. This map is not scalable 
	 * if number of functions are in millions and size of the map increases linearly. Also having it in memory is 
	 * both CPU and memory intensive.
	 *
	 * Moreover this map has to be synchronized in all nodes for coherency and consistency which is another intensive task.
	 * Thus name to pointer function table is at present not implemented. Suitable way to call a function by name of the function
	 * is yet to be found out and references in this topic are scarce.
	 * - Ka.Shrinivaasan
	*/
 
	/*
	*If parameterIsExecutable is set to 2, the data from virgo_clone() is a function and is executed within kernel address-space itself
	*Presently just an example function is invoked. Intermodule function invocation functionality which enables complete takeover
	*of lowlevel system cards, PCI, RAM etc., has been implemented and testcase kern.logs are under ./test_logs/
	*
	*If parameterIsExecutable is set to 1 the data received from virgo_clone() is not a function but name of executable
	*This executable is then run on usermode using call_usermodehelper() which internally takes care of queueing the workstruct
	*and executes the binary as child of keventd and reaps silently. Thus workqueue component of kernel is indirectly made use of.
	*This is sometimes more flexible alternative that executes a binary itself on cloud and 
	*is preferable to clone()ing a function on cloud. Virgo_clone() syscall client or telnet needs to send the message with name of binary.
	*
	*If parameterIsExecutable is set to 0 then data received from virgo_clone() is name of a function and is executed in else clause
	*using dlsym() lookup and pthread_create() in user space. This unifies both call_usermodehelper() and creating a userspace thread
	*with a fixed binary which is same for any function. The dlsym lookup requires mangled function names which need to be sent by 
	*virgo_clone or telnet. This is far more efficient than a function pointer table. 
	*call_usermodehelper() Kernel upcall to usermode to exec a fixed binary that would inturn execute the cloneFunction in userspace
	*by spawning a pthread. cloneFunction is name of the function and not binary. This clone function will be dlsym()ed 
	*and a pthread will be created by the fixed binary. Name of the fixed binary is hardcoded herein as 
	*"virgo_kernelupcall_plugin". This fixed binary takes clone function as argument. For testing libvirgo.so has been created from
	*virgo_cloud_test.c and separate build script to build the cloud function binaries has been added.
	*
	*- Ka.Shrinivaasan
	*/

	int ret=0;
	char *argv[8];
	char *envp[3];

	if (parameterIsExecutable==2)
	{
		struct task_struct *task;
		int woken_up_2=0;
		printk("clone_func(): creating kernel thread and waking up, parameterIsExecutable=%d\n", parameterIsExecutable);
		/*
		int (*virgo_cloud_test_kernelspace)(void*);
		virgo_cloud_test_kernelspace=kallsyms_lookup_name(cloneFunction);
		*/
		if(use_as_kingcobra_service==1)
                {
			/*
				Incoming request data from telnet/virgo_clone() system call into cpupooling kernel service reactor pattern
				is treated as generic string and handed over to VIRGO queue and KingCobra which publishes it
			*/
                        printk("clone_func(): VIRGO cloudexec is used as KingCobra service, invoking push_request() in kernelspace for data: %s\n",args);
			struct virgo_request *vrq=kmalloc(sizeof(struct virgo_request),GFP_ATOMIC);
			vrq->data=kstrdup(args,GFP_ATOMIC);
			vrq->next=NULL;
			push_request(vrq);
			/*
			task=kthread_create(push_request, (void*)args, "KingCobra push_request() thread");
			woken_up_2=wake_up_process(task);
			*/
                }
		else
		{
			task=kthread_create(virgo_cloud_test_kernelspace, (void*)args, "cloneFunction thread");
			woken_up_2=wake_up_process(task);
		}
	}
	else if(parameterIsExecutable==1)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		argv[0]=kstrdup(cloneFunction,GFP_ATOMIC);
		/*
		argv[2]=kstrdup(strcat(argv[2], " >> /home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_kernelupcall_plugin_userspace_exec.log"),GFP_ATOMIC);
		*/
		argv[1]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		/* call_usermodehelper() Kernel upcall to usermode */
		/* cloneFunction contains name of the binary and not the name of the function */
		printk("clone_func(): executing call_usermodehelper for data from virgo_clone: %s - parameterIsExecutable=%d\n",cloneFunction, parameterIsExecutable);	
		ret=call_usermodehelper(cloneFunction, argv, envp, UMH_WAIT_EXEC);
		/*ret=call_usermodehelper("/bin/bash", argv, envp, UMH_WAIT_PROC);*/
		printk("clone_func(): call_usermodehelper() for binary %s returns ret=%d\n", cloneFunction, ret);
		filp_close(file_stdout,NULL);
	}
	else if (parameterIsExecutable==0)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		argv[0]=kstrdup("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_kernelupcall_plugin",GFP_ATOMIC);
		argv[1]=kstrdup(cloneFunction,GFP_ATOMIC);
		argv[2]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games::/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		printk(KERN_INFO "clone_func(): executing the virgo_clone() syscall function parameter in cloud - parameterIsExecutable=%d, cloneFunction=%s\n",parameterIsExecutable,cloneFunction);
		ret=call_usermodehelper("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_kernelupcall_plugin",argv,envp,UMH_WAIT_EXEC);

		/*
		argv[0]=kstrdup("/bin/bash",GFP_ATOMIC);
		argv[1]=kstrdup("-c",GFP_ATOMIC);
		argv[2]=kstrdup("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_kernelupcall_plugin",GFP_ATOMIC);
		argv[3]=kstrdup(cloneFunction,GFP_ATOMIC);
		argv[4]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		printk(KERN_INFO "clone_func(): executing the virgo_clone() syscall function parameter in cloud - parameterIsExecutable=%d\n",parameterIsExecutable);
		ret=call_usermodehelper("/bin/bash",argv,envp,UMH_WAIT_PROC);
		*/
		printk("clone_func(): call_usermodehelper() for virgo_kernelupcall_plugin returns ret=%d\n", ret);
		/*
		Depending on scheduling priority either this or other message in virgocloudexec_sendto() will be sent to
		virgo_clone() remote syscall
		*/
		strcpy(buffer,"clone_func(): cloudclonethread executed for clone_func(), sending message to virgo_clone() remote syscall client");
		filp_close(file_stdout,NULL);
	}
	return 1;
}

char* strip_control_M(char* str)
{
	char* dupstr=kstrdup(str, GFP_ATOMIC);
	char* newstr=strsep(&dupstr, "\r\n ");
	return newstr;
}

int kernel_space_func(void* args)
{
	printk(KERN_INFO "kernel_space_func(): parameterIsExecutable=2; executing function in kernel address space\n");
	return 0;
}

void virgocpupooling_read_virgo_config()
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

	virgocpupooling_node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("virgocpupooling_node_ip_addrs_in_cloud");
	virgocpupooling_num_cloud_nodes=kallsyms_lookup_name("virgocpupooling_num_cloud_nodes");

	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgo_cloud config being read... \n");
	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgocpupooling_num_cloud_nodes=%d #### virgocpupooling_node_ip_addrs_in_cloud=%s\n", virgocpupooling_num_cloud_nodes,virgocpupooling_node_ip_addrs_in_cloud);
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

	for(k=0; k < virgocpupooling_num_cloud_nodes; k++)	
		printk(KERN_INFO "virgo kernel service: read_virgo_config(): before reading virgo_cloud.conf - virgo_cloud ip address - %d: %s\n", k+1, virgocpupooling_node_ip_addrs_in_cloud[k]);

	printk(KERN_INFO "read_virgo_config(): virgo_cloud config file being read \n");


	if(f !=NULL)
	{
		/*f->f_op->read(f, buf, sizeof(buf), &f->f_pos);*/
		bytesread=vfs_read(f, buf, 256, &pos);
		/*strcpy(virgocpupooling_node_ip_addrs_in_cloud[i],buf);*/
		printk(KERN_INFO "do_virgo_cloud_init(): virgo_cloud config file string of comma separated IPs : %s \n",buf);
		/*printk(KERN_INFO "do_virgo_cloud_init(): virgo_cloud config file line %d \n",i);*/
		pos=pos+bytesread;
	}
	/*virgocpupooling_num_cloud_nodes=tokenize_list_of_ip_addrs(buf);*/
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): %s\n",token);
		virgocpupooling_node_ip_addrs_in_cloud[i]=kstrdup(token,GFP_ATOMIC);
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): virgocpupooling_node_ip_addrs_in_cloud[%d] = %s\n",i,virgocpupooling_node_ip_addrs_in_cloud[i]);
		i++;
	}
	virgocpupooling_num_cloud_nodes=i;
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
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO, "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	int i=0;
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO, "tokenize_list_of_ip_addrs(): %s\n",token);
		/*strcpy(virgocpupooling_node_ip_addrs_in_cloud[i],  token);*/
		i++;
	}
	return i;
}

/*
FPTR get_function_ptr_from_str(char* cloneFunction)
{
	return clone_func;
}
*/

static int __init
virgocloudexec_init(void)
{
	printk(KERN_INFO "virgocloudexec_init(): doing init() of virgocloudexec kernel module\n");
	printk(KERN_INFO "virgocloudexec_init(): starting virgo cloudexec service kernel thread\n");
	
	printk(KERN_INFO "virgocloudexec_init(): invoking read_virgo_config()\n");
	virgocpupooling_read_virgo_config();

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

	/*
	file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloudexec_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
	fd_install(1,file_stdout);
	fd_install(2,file_stdout);
	*/
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_init);

int virgocloudexec_create(void)
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
	printk(KERN_INFO "virgocloudexec_create(): kernel_accept() returns error code: %d\n",error);
	printk(KERN_INFO "virgocloudexec_create(): kernel_accept() clientsock: %u\n",clientsock);
	return clientsock;
}
EXPORT_SYMBOL(virgocloudexec_create);

int virgocloudexec_recvfrom(struct socket* clsock)
{
	/*
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/
	char* cloneFunction;
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
#ifdef LINUX_KERNEL_4_x_x
                msg.msg_iter.iov = &iov;
#else
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
#endif
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
		cloneFunction = strip_control_M(kstrdup(buffer,GFP_ATOMIC));
		if(use_as_kingcobra_service==1)
		{
	                client_ip_str=kmalloc(BUF_SIZE,GFP_ATOMIC);
                        struct sockaddr_in* ipaddr=(struct sockaddr_in*)clientsock;
                        long ipaddr_int = ntohl(ipaddr->sin_addr.s_addr);
                        /*inet_ntop(AF_INET, &ipaddr_int, client_ip_str, BUF_SIZE);*/
                        sprintf(client_ip_str,"%x",ipaddr_int);
                        printk(KERN_INFO "virgocloudexec_cpupool_recvfrom(): client_ip_str = %s\n",client_ip_str);
                        client_ip_str=kstrdup(strcat(client_ip_str,"#"),GFP_ATOMIC);
                        printk(KERN_INFO "virgocloudexec_cpupool_recvfrom(): client_ip_str with # appended = %s\n",client_ip_str);
                        char* request_header=kmalloc(BUF_SIZE,GFP_ATOMIC);
                        sprintf(request_header,"REQUEST#");
                        request_header=kstrdup(strcat(request_header,client_ip_str),GFP_ATOMIC);
                        char* logicaltimestamp=generate_logical_timestamp();
                        request_header=kstrdup(strcat(request_header,logicaltimestamp),GFP_ATOMIC);
                        cloneFunction = kstrdup(strcat(request_header,cloneFunction),GFP_ATOMIC);
                        printk(KERN_INFO "virgocloudexec_cpupool_recvfrom(): use_as_kingcobra_service=1, mempoolFunction with prepended request header and client ip=%s\n",cloneFunction);
		}
		/*cloneFunction[strlen(cloneFunction)-2]='\0';*/
		
		printk(KERN_INFO "virgocloudexec_recvfrom(): kernel_recvmsg() returns in recv buffer: %s\n", buffer);
		print_buffer(buffer);
		le32_to_cpus(buffer);
		printk(KERN_INFO "virgocloudexec_recvfrom(): kernel_recvmsg() le32 to cpu %s\n", buffer);
		printk(KERN_INFO "virgocloudexec_recvfrom(): cloneFunction : %s \n", cloneFunction);
		/*cloneFunction_ptr = get_function_ptr_from_str(cloneFunction);*/
		/*task=kthread_run(cloneFunction_ptr, (void*)args, "cloudclonethread");*/
		args=(void*)cloneFunction;

		/* 
			Invoking clone_func() directly instead of a kernel thread as clone_func() itself
			spawns a kernel thread 
		*/
		clone_func(cloneFunction);

		/*
		task=kthread_create(clone_func, (void*)args, "clone_func thread");
		int woken_up=wake_up_process(task);
		printk(KERN_INFO "virgocloudexec_recvfrom(): clone thread woken_up : %d\n",woken_up);
		task=kthread_create(clone_func, (void*)args, "cloudclonethread");
		*/
		strcpy(buffer,"cloudclonethread executed");
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

int virgocloudexec_sendto(struct socket* clsock)
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
#ifdef LINUX_KERNEL_4_x_x
                msg.msg_iter.iov = &iov;
#else
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
#endif
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
	/*filp_close(file_stdout,NULL);*/
	do_exit(1);
}
EXPORT_SYMBOL(virgocloudexec_exit);

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



MODULE_LICENSE("GPL");
module_init(virgocloudexec_init);
module_exit(virgocloudexec_exit);
