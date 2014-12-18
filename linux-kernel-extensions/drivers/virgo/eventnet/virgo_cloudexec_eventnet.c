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

#include <linux/virgo_eventnet.h>
#include <linux/virgocloudexeceventnetsvc.h>
#include <linux/virgo_config.h>

#include <linux/string.h>
#include <linux/kallsyms.h>

extern void virgo_eventnet_log(char*);

/*
	VIRGO Cloud EventNet Kernel Module
*/


char* eventnet_func(void* args)
{
	char buffer[BUF_SIZE];
	int ret=0;
	char *argv[8];
	char *envp[3];
	char* eventnetFunction = (char*)args;
	struct virgo_eventnet_args* vmargs=parse_virgoeventnet_command(kstrdup(eventnetFunction,GFP_KERNEL));

	if (parameterIsExecutable==2)
	{
		struct task_struct *task;
		int woken_up_2=0;
		printk(KERN_INFO "eventnet_func(): creating kernel thread and waking up, parameterIsExecutable=%d\n", parameterIsExecutable);
		printk(KERN_INFO "Creating Kernel Thread for %s in virgo_cloud_eventnet_kernelspace eventnet driver module ",vmargs->event_message_type);

		toFuncPtr(kstrdup(strcat(kstrdup(vmargs->event_message_type,GFP_KERNEL),"_kernelspace"),GFP_KERNEL))(vmargs);

		/*
		woken_up_2=wake_up_process(task);
		*/
	}
	else if(parameterIsExecutable==1)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgo_cloudexec_eventnet_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		argv[0]=kstrdup(eventnetFunction,GFP_KERNEL);
		argv[1]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		/* call_usermodehelper() Kernel upcall to usermode */
		/* eventnetFunction contains name of the binary and not the name of the function */
		printk("fs_func(): executing call_usermodehelper for data from virgo_fs : %s - parameterIsExecutable=%d\n",eventnetFunction, parameterIsExecutable);	
		ret=call_usermodehelper(eventnetFunction, argv, envp, UMH_WAIT_EXEC);
		printk("fs_func(): call_usermodehelper() for binary %s returns ret=%d\n", eventnetFunction, ret);
		filp_close(file_stdout,NULL);
	}
	else if (parameterIsExecutable==0)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgo_cloudexec_eventnet_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		/*
		Commented fd_install() due to crashes which were working in cpupooling driver. Same crash was occuring in memorypooling driver
		also few months ago. Probably some other process has already done fd_install to these fd(s).
		- Ka.Shrinivaasan 5May2014
		*/
		/*
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		*/
		argv[0]=kstrdup("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgo_kernelupcall_plugin",GFP_KERNEL);
		argv[1]=kstrdup(eventnetFunction,GFP_KERNEL);
		argv[2]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games::/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		printk(KERN_INFO "fs_func(): executing the virgo_fs function parameter in cloud - parameterIsExecutable=%d, eventnetFunction=%s\n",parameterIsExecutable,eventnetFunction);
		ret=call_usermodehelper("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/virgo_kernelupcall_plugin",argv,envp,UMH_WAIT_EXEC);

		printk("fs_func(): call_usermodehelper() for virgo_kernelupcall_plugin returns ret=%d\n", ret);
		/*
		Depending on scheduling priority either this or other message in virgocloudexec_eventnet_sendto() will be sent to
		virgo_fs remote syscall
		*/
		strcpy(buffer,"fs_func(): cloudclonethread executed for fs_func(), sending message to virgo_malloc() remote syscall client");
		filp_close(file_stdout,NULL);
	}
	return "EventNet updated";
}

char* strip_control_M(char* str)
{
        printk("strip_control_M(): str=%s before strsep\n",str);
        char* dupstr=kstrdup(str, GFP_KERNEL);
        char* newstr=strsep(&dupstr, "\r\n");
        printk("strip_control_M(): newstr=%s after carriage return newline strsep\n",newstr);
        return newstr;
}

int kernel_space_func(void* args)
{
	printk(KERN_INFO "kernel_space_func(): parameterIsExecutable=2; executing function in kernel address space\n");
	return 0;
}

void virgoeventnet_read_virgo_config()
{
	/* virgo_cloud.conf contains a string of comma separated list of IP addresses in the virgo cloud .Read and strsep() it. */

	loff_t bytesread=0;
	loff_t pos=0;
	mm_segment_t fs;

	/*
	 * It is redundant to use kallsyms_lookup for exported symbols for virgo cloud initialization. 
	 * kallsyms_lookup is for non-exported symbols.
	 * 
	 * - Ka.Shrinivaasan 10 July 2013
	 *

	virgofs_node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("virgofs_node_ip_addrs_in_cloud");
	virgofs_num_cloud_nodes=kallsyms_lookup_name("virgofs_num_cloud_nodes");

	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgo_cloud config being read... \n");
	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgofs_num_cloud_nodes=%d #### virgofs_node_ip_addrs_in_cloud=%s\n", virgofs_num_cloud_nodes,virgofs_node_ip_addrs_in_cloud);
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

	for(k=0; k < virgoeventnet_num_cloud_nodes; k++)	
		printk(KERN_INFO "virgo kernel service: read_virgo_config(): before reading virgo_cloud.conf - virgo_cloud ip address - %d: %s\n", k+1, virgofs_node_ip_addrs_in_cloud[k]);

	printk(KERN_INFO "read_virgo_config(): virgo_cloud config file being read \n");


	if(f !=NULL)
	{
		bytesread=vfs_read(f, buf, 256, &pos);
		printk(KERN_INFO "do_virgo_cloud_init(): virgo_cloud config file string of comma separated IPs : %s \n",buf);
		pos=pos+bytesread;
	}
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_KERNEL);
	printk(KERN_INFO "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): %s\n",token);
		virgoeventnet_node_ip_addrs_in_cloud[i]=kstrdup(token,GFP_KERNEL);
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): virgoeventnet_node_ip_addrs_in_cloud[%d] = %s\n",i,virgoeventnet_node_ip_addrs_in_cloud[i]);
		i++;
	}
	virgoeventnet_num_cloud_nodes=i;
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
		/*strcpy(virgofs_node_ip_addrs_in_cloud[i],  token);*/
		i++;
	}
	return i;
}


static int __init
virgocloudexec_eventnet_init(void)
{
	int error;
	static struct sockaddr_in sin;

	printk(KERN_INFO "virgocloudexec_eventnet_init(): doing init() of virgocloudexec_eventnet kernel module\n");
	printk(KERN_INFO "virgocloudexec_eventnet_init(): starting virgo cloudexec service kernel thread\n");
	
	printk(KERN_INFO "virgocloudexec_eventnet_init(): invoking read_virgo_config()\n");
	virgoeventnet_read_virgo_config();

	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	sin.sin_port=htons(20000);

	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgocloudexec_eventnet_init(): sock_create() returns error code: %d\n",error);

	error = kernel_bind(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	printk(KERN_INFO "virgocloudexec_eventnet_init(): kernel_bind() returns error code: %d\n",error);

	error = kernel_listen(sock, 2);
	printk(KERN_INFO "virgocloudexec_eventnet_init(): kernel_listen() returns error code: %d\n", error);

	virgo_cloudexec_eventnet_service(NULL);

	return 0;
}
EXPORT_SYMBOL(virgocloudexec_eventnet_init);

int virgocloudexec_eventnet_create(void)
{
	int error;

	/*
	Blocking mode works in this commit again. No changes were made in virgo_malloc() or driver code. 
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
		printk(KERN_INFO "virgocloudexec_eventnet_create():kernel_accept() returns -EAGAIN\n");
	return clientsock;
}
EXPORT_SYMBOL(virgocloudexec_eventnet_create);

void* virgocloudexec_eventnet_recvfrom(struct socket* clsock)
{
	char* eventnetFunction;
	struct sockaddr_in sin;
	void* virgo_eventnet_func_ret;

	/* example virgo eventnet_log */
	/*virgo_eventnet_log("eventnet_edgemsg#1#2#");*/

	/*
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/
	struct socket *clientsock=clsock;
	struct kvec iov;
	struct msghdr msg = { NULL, };
	int buflen=BUF_SIZE;
	void *args=NULL;
	int nr=1;

	struct task_struct *task;
	int error;
	char buffer[BUF_SIZE];
	int len=0;

	char* client_ip_str;

	/*	
		do kernel_recvmsg() to get the function data to be executed on a thread
	*/
	if(clientsock != NULL )
	{
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): before kernel_recvmsg()\n");
		memset(buffer, 0, BUF_SIZE);
		iov.iov_base=(void*)buffer;
		iov.iov_len=BUF_SIZE;	
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags=MSG_NOSIGNAL;

		len  = kernel_recvmsg(clientsock, &msg, &iov, 1, buflen, msg.msg_flags);
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): kernel_recvmsg() returns len: %d\n",len);
		/*
			parse the message and invoke kthread_create()
			do kernel_sendmsg() with the results
		*/
		eventnetFunction = strip_control_M(kstrdup(buffer,GFP_KERNEL));
		
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): kernel_recvmsg() returns in recv: iov.iov_base=%s, buffer: %s\n", iov.iov_base, buffer);
		/*
		print_buffer(buffer);
		le32_to_cpus(buffer);
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): kernel_recvmsg() le32 to cpu %s\n", buffer);
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): eventnetFunction : %s \n", eventnetFunction);
		*/
		args=(void*)eventnetFunction;

		/*
		Temporarily commenting kthread creation for the kernelspace virgo eventnet ops 
		execution as return value from a kthread function is needed which is difficult 
		and circuitous to do with kthread. Instead the fs_func is directly invoked.
		*/
		/*task=kthread_create(eventnet_func, (void*)args, "eventnet_func thread");*/
		virgo_eventnet_func_ret=eventnet_func((void*)args);

		/*
		int woken_up=wake_up_process(task);
		printk(KERN_INFO "virgocloudexec_eventnet_recvfrom(): clone thread woken_up : %d\n",woken_up);
		*/

	}
	return virgo_eventnet_func_ret;
}
EXPORT_SYMBOL(virgocloudexec_eventnet_recvfrom);

void print_buffer(char* buffer)
{
	printk(KERN_INFO "virgo_cloudexec_eventnet: print_buffer(): ");
	int i=0;
	for(i=0; i < BUF_SIZE; i++)
		printk(KERN_INFO "%c", buffer[i]);
	printk(KERN_INFO "\n");
}

int virgocloudexec_eventnet_sendto(struct socket* clsock, void* virgo_eventnet_ret)
{

	/*
	Multithreaded VIRGO Kernel Service
	----------------------------------
	*/

	struct sockaddr_in sin;
	struct socket *clientsock=clsock;
	struct kvec iov;
	struct msghdr msg = { NULL, };
	int buflen=BUF_SIZE;
	void *args=NULL;
	int nr=1;

	struct task_struct *task;
	int error;
	char buffer[BUF_SIZE];
	int len=0;

	if(clientsock != NULL)
	{
	
		printk(KERN_INFO "virgocloudexec_eventnet_sendto(): virgo_eventnet_ret=%s\n",virgo_eventnet_ret);
		if(virgo_eventnet_ret != NULL)
		{
			printk(KERN_INFO "virgocloudexec_eventnet_sendto(): data sent=%s\n",virgo_eventnet_ret);
			strcpy(buffer,virgo_eventnet_ret);
		}
		iov.iov_base=buffer;	
		iov.iov_len=BUF_SIZE;
		msg.msg_name = (struct sockaddr *) &sin;
		msg.msg_namelen = sizeof(struct sockaddr);
		msg.msg_iov = (struct iovec *) &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags=0;

		int ret;
		printk(KERN_INFO "virgocloudexec_eventnet_sendto(): before kernel_sendmsg() for send buffer: %s\n", buffer);
		ret = kernel_sendmsg(clientsock, &msg, &iov, 1, buflen);
		printk(KERN_INFO "virgocloudexec_eventnet_sendto(): kernel_sendmsg() returns ret: %d\n",ret);
		sock_release(clientsock);
		printk(KERN_INFO "virgocloudexec_eventnet_sendto(): sock_release invoked on client socket \n");
	}
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_eventnet_sendto);


static void __exit
virgocloudexec_eventnet_exit(void)
{
	printk(KERN_INFO "exiting virgocloudexec_eventnet kernel module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgocloudexec_eventnet_exit);

/*
Arguments Parser for VIRGO EventNet logging messages from remote client:
Edge message - "eventnet_edgemsg#<eventid>#<from_event>#<to_event>"
Vertex message - "eventnet_vertextmsg#<eventid>#<partakers csv>#<partaker conversations csv>"
*/

struct virgo_eventnet_args* parse_virgoeventnet_command(char* eventnetFunction)
{
	struct virgo_eventnet_args* vmargs=kmalloc(sizeof(struct virgo_eventnet_args),GFP_KERNEL);
	vmargs->event_message_type=kstrdup(strsep(&eventnetFunction, "#"),GFP_KERNEL);
        printk(KERN_INFO "parse_virgoeventnet_command: vmargs->event_message_type: %s\n", vmargs->event_message_type);

	if(strcmp(vmargs->event_message_type,"eventnet_vertexmsg")==0)
	{
		/* vertexmsg */
		vmargs->event_id=kstrdup(strsep(&eventnetFunction,"#"),GFP_KERNEL);
		printk(KERN_INFO "parse_virgoeventnet_command: vmargs->event_id: %s\n", vmargs->event_id);
		vmargs->eventid_args[0]=kstrdup(strsep(&eventnetFunction,"#"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgoeventnet_command: vmargs->eventid_args[0]: %s\n", vmargs->eventid_args[0]);
		vmargs->eventid_args[1]=kstrdup(strsep(&eventnetFunction,"#"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgoeventnet_command: vmargs->eventid_args[1]: %s\n", vmargs->eventid_args[1]);
	}
	else if(strcmp(vmargs->event_message_type,"eventnet_edgemsg")==0)
	{
		/* edgemsg */
		vmargs->eventid_args[0]=kstrdup(strsep(&eventnetFunction,"#"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgoeventnet_command: vmargs->eventid_args[0]: %s\n", vmargs->eventid_args[0]);
		vmargs->eventid_args[1]=kstrdup(strsep(&eventnetFunction,"#"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgoeventnet_command: vmargs->eventid_args[1]: %s\n", vmargs->eventid_args[1]);
	}	
	return vmargs;
}

FPTR toFuncPtr(char* functionName)
{
        if(strcmp(functionName, "eventnet_vertexmsg_kernelspace")==0)
                return virgo_cloud_eventnet_vertexmsg_kernelspace;
        if(strcmp(functionName, "eventnet_edgemsg_kernelspace")==0)
                return virgo_cloud_eventnet_edgemsg_kernelspace;
}

MODULE_LICENSE("GPL");
module_init(virgocloudexec_eventnet_init);
module_exit(virgocloudexec_eventnet_exit);
