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
Copyright (C):
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Independent Open Source Developer, Researcher and Consultant
Ph: 9789346927, 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#include <linux/virgo_fs.h>
#include <linux/virgocloudexecfssvc.h>
#include <linux/virgo_config.h>

#include <linux/string.h>
#include <linux/kallsyms.h>

/*
	VIRGO File Systems Driver for virgo_open(), virgo_close(),virgo_read(),virgo_write()
*/


/*
* The wrapper function that based on switch parameterIsExecutable (values 0,1,2) executes the binary or function data from virgo_fs
* system calls or telnet connections in either kernel or user address-spaces
* - Ka.Shrinivaasan
*/
 
int fs_func(void* args)
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
	*If parameterIsExecutable is set to 2, the data from virgo_fs client is a function and is executed within kernel address-space itself
	*This invokes kmalloc() to allocate kernel memory. Intermodule function invocation functionality which enables complete takeover
	*of lowlevel system cards, PCI, RAM etc., has been implemented
	*
	*If parameterIsExecutable is set to 1 the data received from virgo_fs is not a function but name of executable
	*This executable is then run on usermode using call_usermodehelper() which internally takes care of queueing the workstruct
	*and executes the binary as child of keventd and reaps silently. Thus workqueue component of kernel is indirectly made use of.
	*This is sometimes more flexible alternative that executes a binary itself on cloud and 
	*is preferable to clone()ing a function on cloud. Virgo_fs syscall client or telnet needs to send the message with name of binary.
	*
	*If parameterIsExecutable is set to 0 then data received from virgo_fs client is name of a function and is executed in else clause
	*using dlsym() lookup and pthread_create() in user space. This unifies both call_usermodehelper() and creating a userspace thread
	*with a fixed binary which is same for any function. The dlsym lookup requires mangled function names which need to be sent by 
	*virgo_fs syscalls or telnet. This is far more efficient than a function pointer table. 
	*call_usermodehelper() Kernel upcall to usermode to exec a fixed binary that would inturn execute the fsFunction in userspace
	*by spawning a pthread. fsFunction is name of the function and not binary. This clone function will be dlsym()ed 
	*and a pthread will be created by the fixed binary. Name of the fixed binary is hardcoded herein as 
	*"virgo_kernelupcall_plugin". This fixed binary takes malloc function as argument. For testing libvirgo_fs.so has been created from
	*virgo_cloud_test.c and separate build script to build the cloud function binaries has been added.
	*
	*- Ka.Shrinivaasan
	*/

	char buffer[BUF_SIZE];
	int ret=0;
	char *argv[8];
	char *envp[3];
	char* fsFunction = (char*)args;
	struct virgo_fs_args* vmargs=parse_virgofs_command(kstrdup(fsFunction,GFP_KERNEL));
	void* virgo_fs_ret;

	if (parameterIsExecutable==2)
	{
		struct task_struct *task;
		int woken_up_2=0;
		printk(KERN_INFO "fs_func(): creating kernel thread and waking up, parameterIsExecutable=%d\n", parameterIsExecutable);
		printk(KERN_INFO "Creating Kernel Thread for %s in virgo_cloud_fs_kernelspace fs driver module with fs_args[0]=%s, fs_args[1]=%s\n",vmargs->fs_cmd,vmargs->fs_args[0],vmargs->fs_args[1]);

		/*
		Temporarily commenting kthread creation for the kernelspace virgo fs
		ops execution as return value from a kthread function is needed which is
		difficult and circuitous to do with kthread. Instead the functions in the
		kernel module virgo_cloud_fs_kernelspace.ko are directly invoked using
		intermodule kernelspace invocation.
		*/
		/*task=kthread_create(toFuncPtr(kstrdup(strcat(vmargs->fs_cmd,"_kernelspace"),GFP_KERNEL)), (void*)vmargs, "fsFunction kernelspace thread");*/
		virgo_fs_ret=toFuncPtr(kstrdup(strcat(kstrdup(vmargs->fs_cmd,GFP_KERNEL),"_kernelspace"),GFP_KERNEL))(vmargs);

		printk(KERN_INFO "fs_func(): virgo fs kernelspace module returns value virgo_fs_ret=%p\n", (char*)virgo_fs_ret);
		/*
		woken_up_2=wake_up_process(task);
		*/
	}
	else if(parameterIsExecutable==1)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/virgo_cloudexec_fs_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		argv[0]=kstrdup(fsFunction,GFP_KERNEL);
		argv[1]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		/* call_usermodehelper() Kernel upcall to usermode */
		/* fsFunction contains name of the binary and not the name of the function */
		printk("fs_func(): executing call_usermodehelper for data from virgo_fs : %s - parameterIsExecutable=%d\n",fsFunction, parameterIsExecutable);	
		ret=call_usermodehelper(fsFunction, argv, envp, UMH_WAIT_EXEC);
		printk("fs_func(): call_usermodehelper() for binary %s returns ret=%d\n", fsFunction, ret);
		filp_close(file_stdout,NULL);
	}
	else if (parameterIsExecutable==0)
	{
	        file_stdout=filp_open("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/virgo_cloudexec_fs_upcall_usermode_log.txt", O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
		fd_install(1,file_stdout);
		fd_install(2,file_stdout);
		argv[0]=kstrdup("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/virgo_kernelupcall_plugin",GFP_KERNEL);
		argv[1]=kstrdup(fsFunction,GFP_KERNEL);
		argv[2]=NULL;
		envp[0]="PATH=/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games::/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/";
		envp[1]="HOME=/home/kashrinivaasan";
		envp[2]=NULL;
		printk(KERN_INFO "fs_func(): executing the virgo_malloc() syscall function parameter in cloud - parameterIsExecutable=%d, fsFunction=%s\n",parameterIsExecutable,fsFunction);
		ret=call_usermodehelper("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/fs/virgo_kernelupcall_plugin",argv,envp,UMH_WAIT_EXEC);

		printk("fs_func(): call_usermodehelper() for virgo_kernelupcall_plugin returns ret=%d\n", ret);
		/*
		Depending on scheduling priority either this or other message in virgocloudexec_fs_sendto() will be sent to
		virgo_fs remote syscall
		*/
		strcpy(buffer,"fs_func(): cloudclonethread executed for fs_func(), sending message to virgo_malloc() remote syscall client");
		filp_close(file_stdout,NULL);
	}
	return virgo_fs_ret;
}

char* strip_control_M(char* str)
{
        printk("strip_control_M(): str=%s before strsep\n",str);
        char* dupstr=kstrdup(str, GFP_KERNEL);
        char* newstr=strsep(&dupstr, "\r\n ");
        printk("strip_control_M(): newstr=%s after carriage return newline strsep\n",newstr);
        return newstr;
}

int kernel_space_func(void* args)
{
	printk(KERN_INFO "kernel_space_func(): parameterIsExecutable=2; executing function in kernel address space\n");
	return 0;
}

void read_virgo_config()
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

	node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("node_ip_addrs_in_cloud");
	num_cloud_nodes=kallsyms_lookup_name("num_cloud_nodes");

	printk(KERN_INFO "virgo kernel service: read_virgo_config(): virgo_cloud config being read... \n");
	printk(KERN_INFO "virgo kernel service: read_virgo_config(): num_cloud_nodes=%d #### node_ip_addrs_in_cloud=%s\n", num_cloud_nodes,node_ip_addrs_in_cloud);
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

	for(k=0; k < num_cloud_nodes; k++)	
		printk(KERN_INFO "virgo kernel service: read_virgo_config(): before reading virgo_cloud.conf - virgo_cloud ip address - %d: %s\n", k+1, node_ip_addrs_in_cloud[k]);

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
		node_ip_addrs_in_cloud[i]=kstrdup(token,GFP_KERNEL);
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): node_ip_addrs_in_cloud[%d] = %s\n",i,node_ip_addrs_in_cloud[i]);
		i++;
	}
	num_cloud_nodes=i;
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
		/*strcpy(node_ip_addrs_in_cloud[i],  token);*/
		i++;
	}
	return i;
}


static int __init
virgocloudexec_fs_init(void)
{
	int error;
	static struct sockaddr_in sin;

	printk(KERN_INFO "virgocloudexec_fs_init(): doing init() of virgocloudexec_fs kernel module\n");
	printk(KERN_INFO "virgocloudexec_fs_init(): starting virgo cloudexec service kernel thread\n");
	
	printk(KERN_INFO "virgocloudexec_fs_init(): invoking read_virgo_config()\n");
	read_virgo_config();

	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	sin.sin_port=htons(50000);

	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "virgocloudexec_fs_init(): sock_create() returns error code: %d\n",error);

	error = kernel_bind(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	printk(KERN_INFO "virgocloudexec_fs_init(): kernel_bind() returns error code: %d\n",error);

	error = kernel_listen(sock, 2);
	printk(KERN_INFO "virgocloudexec_fs_init(): kernel_listen() returns error code: %d\n", error);

	virgo_cloudexec_fs_service(NULL);

	return 0;
}
EXPORT_SYMBOL(virgocloudexec_fs_init);

int virgocloudexec_fs_create(void)
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
	/*
	if(error==-EAGAIN)
		printk(KERN_INFO "kernel_accept() returns -EAGAIN\n");
	printk(KERN_INFO "virgocloudexec_fs_create(): kernel_accept() returns error code: %d\n",error);
	printk(KERN_INFO "virgocloudexec_fs_create(): kernel_accept() clientsock: %u\n",clientsock);
	*/
	return clientsock;
}
EXPORT_SYMBOL(virgocloudexec_fs_create);

void* virgocloudexec_fs_recvfrom(struct socket* clsock)
{
	char* fsFunction;
	struct sockaddr_in sin;
	void* virgo_fs_func_ret;

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
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): before kernel_recvmsg()\n");
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
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): kernel_recvmsg() returns len: %d\n",len);
		/*
			parse the message and invoke kthread_create()
			do kernel_sendmsg() with the results
		*/
		fsFunction = strip_control_M(kstrdup(buffer,GFP_KERNEL));
		
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): kernel_recvmsg() returns in recv: iov.iov_base=%s, buffer: %s\n", iov.iov_base, buffer);
		print_buffer(buffer);
		le32_to_cpus(buffer);
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): kernel_recvmsg() le32 to cpu %s\n", buffer);
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): fsFunction : %s \n", fsFunction);
		args=(void*)fsFunction;

		/*
		Temporarily commenting kthread creation for the kernelspace virgo fs ops 
		execution as return value from a kthread function is needed which is difficult 
		and circuitous to do with kthread. Instead the fs_func is directly invoked.
		*/
		/*task=kthread_create(fs_func, (void*)args, "fs_func thread");*/
		virgo_fs_func_ret=fs_func((void*)args);

		/*
		int woken_up=wake_up_process(task);
		printk(KERN_INFO "virgocloudexec_fs_recvfrom(): clone thread woken_up : %d\n",woken_up);
		*/

	}
	return virgo_fs_func_ret;
}
EXPORT_SYMBOL(virgocloudexec_fs_recvfrom);

void print_buffer(char* buffer)
{
	printk(KERN_INFO "virgo_cloudexec_fs: print_buffer(): ");
	int i=0;
	for(i=0; i < BUF_SIZE; i++)
		printk(KERN_INFO "%c", buffer[i]);
	printk(KERN_INFO "\n");
}

int virgocloudexec_fs_sendto(struct socket* clsock, void* virgo_fs_ret)
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
	
		printk(KERN_INFO "virgocloudexec_fs_sendto(): virgo_fs_ret=%s\n",virgo_fs_ret);
		if(virgo_fs_ret != NULL)
		{
			/* 
				VFS file descriptor allocated by VFS kernelspace is sent to the remote client that is used in 
				subsequent read/write calls
				- Ka.Shrinivaasan 4 May 2014
			*/	
			printk(KERN_INFO "virgocloudexec_fs_sendto(): data sent=%s\n",virgo_fs_ret);
			strcpy(buffer,virgo_fs_ret);
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
		printk(KERN_INFO "virgocloudexec_fs_sendto(): before kernel_sendmsg() for send buffer: %s\n", buffer);
		ret = kernel_sendmsg(clientsock, &msg, &iov, 1, buflen);
		printk(KERN_INFO "virgocloudexec_fs_sendto(): kernel_sendmsg() returns ret: %d\n",ret);
		sock_release(clientsock);
		printk(KERN_INFO "virgocloudexec_fs_sendto(): sock_release invoked on client socket \n");
	}
	return 0;
}
EXPORT_SYMBOL(virgocloudexec_fs_sendto);


static void __exit
virgocloudexec_fs_exit(void)
{
	printk(KERN_INFO "exiting virgocloudexec_fs kernel module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgocloudexec_fs_exit);

/*
Arguments Parser for VIRGO memory pooling commands-virgo_cloud_malloc,virgo_cloud_free
virgo_cloud_set,virgo_cloud_get- sent from virgo_malloc syscall
*/

struct virgo_fs_args* parse_virgofs_command(char* fsFunction)
{
	struct virgo_fs_args* vmargs=kmalloc(sizeof(struct virgo_fs_args),GFP_KERNEL);
	vmargs->fs_cmd=kstrdup(strsep(&fsFunction, "("),GFP_KERNEL);
        printk(KERN_INFO "parse_virgofs_command: vmargs->fs_cmd: %s\n", vmargs->fs_cmd);

	if(strcmp(vmargs->fs_cmd,"virgo_cloud_open")==0 || strcmp(vmargs->fs_cmd,"virgo_cloud_close")==0)
	{
		vmargs->fs_args[0]=kstrdup(strsep(&fsFunction,")"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgofs_command: vmargs->fs_args[0]: %s\n", vmargs->fs_args[0]);
		vmargs->fs_args[1]=NULL;
	}
	else
	{
		vmargs->fs_args[0]=kstrdup(strsep(&fsFunction,","),GFP_KERNEL);
		vmargs->fs_args[1]=kstrdup(strsep(&fsFunction,","),GFP_KERNEL);
		vmargs->fs_args[2]=kstrdup(strsep(&fsFunction,","),GFP_KERNEL);
		vmargs->fs_args[3]=kstrdup(strsep(&fsFunction,")"),GFP_KERNEL);
        	printk(KERN_INFO "parse_virgofs_command: vmargs->fs_args[0]: %s\n", vmargs->fs_args[0]);
        	printk(KERN_INFO "parse_virgofs_command: vmargs->fs_args[1]: %s\n", vmargs->fs_args[1]);
        	printk(KERN_INFO "parse_virgofs_command: vmargs->fs_args[2]: %d\n", vmargs->fs_args[2]);
        	printk(KERN_INFO "parse_virgofs_command: vmargs->fs_args[3]: %d\n", vmargs->fs_args[3]);
		vmargs->fs_args[4]=NULL;
	}	
	return vmargs;
}

FPTR toFuncPtr(char* functionName)
{
        if(strcmp(functionName, "virgo_cloud_open_kernelspace")==0)
                return virgo_cloud_open_kernelspace;
        if(strcmp(functionName, "virgo_cloud_close_kernelspace")==0)
                return virgo_cloud_close_kernelspace;
        if(strcmp(functionName, "virgo_cloud_read_kernelspace")==0)
                return virgo_cloud_read_kernelspace;
        if(strcmp(functionName, "virgo_cloud_write_kernelspace")==0)
                return virgo_cloud_write_kernelspace;
}

MODULE_LICENSE("GPL");
module_init(virgocloudexec_fs_init);
module_exit(virgocloudexec_fs_exit);
