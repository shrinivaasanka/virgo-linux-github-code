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


#include <linux/string.h>
#include <linux/virgo.h>
#include <linux/module.h>
#include <linux/string.h>
#include <kstrtox.h>
#include <linux/ctype.h>

char *eventnet_kernel_service_host="127.0.0.1";

static int __init
virgo_generic_kernelsock_client_init(void)
{
	printk(KERN_INFO "virgo_generic_kernelsock_client_init(): initialising virgo cloud test kernel space module \n");
	return 0;
}
EXPORT_SYMBOL(virgo_generic_kernelsock_client_init);

void virgo_eventnet_log(char* logmsg)
{
        char buf[BUF_SIZE];
	char tempbuf[BUF_SIZE];
        int sfd, s, j;
        size_t len;
        ssize_t nread;
	struct msghdr msg;
	int error;
	int nr;
	struct kvec iov;
	char* hostip = eventnet_kernel_service_host;
	int port=20000;
	struct socket *sock;
	struct sockaddr_in sin;
	in4_pton(hostip, strlen(hostip), &sin.sin_addr.s_addr, '\0',NULL);
	sin.sin_family=AF_INET;
       	sin.sin_port=htons(port);
	printk(KERN_INFO "eventnet_log() : after in4_pton and htons, hostip=%s, port=%d, sin.sin_addr.s_addr=%x, sin.sin_port=%x\n", hostip, port, sin.sin_addr.s_addr, sin.sin_port);
	strcpy(buf,logmsg);

	iov.iov_base=buf;
	iov.iov_len=strlen(buf);
	msg.msg_name = (struct sockaddr *) &sin;
	msg.msg_namelen = sizeof(struct sockaddr);
	msg.msg_iov = (struct iovec *) &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	nr=1;
	
	/*strcpy(iov.iov_base, buf);*/
	error = sock_create_kern(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
	printk(KERN_INFO "eventnet_log() : created client kernel socket\n");
	kernel_connect(sock, (struct sockaddr*)&sin, sizeof(sin) , 0);
	printk(KERN_INFO "eventnet_log() : connected kernel client to virgo cloudexec EventNet kernel service\n ");
	len = kernel_sendmsg(sock, &msg, &iov, nr, BUF_SIZE);
	printk(KERN_INFO "eventnet_log() : sent len=%d; iov.iov_base=%s, sent message: %s \n", len, iov.iov_base, buf);
       	len = kernel_recvmsg(sock, &msg, &iov, nr, BUF_SIZE, msg.msg_flags);
	printk(KERN_INFO "eventnet_log() : recv len=%d; received message buf: [%s] \n", len, buf);
	printk(KERN_INFO "eventnet_log() : received iov.iov_base: %s \n", iov.iov_base);

	le32_to_cpus(buf);
	printk(KERN_INFO "eventnet_log() : le32_to_cpus(buf): %s \n", buf);

	/*
	Mysteriously sock_release() causes kernel panic repeatedly. Hence commenting this
	temporarily.
	- Ka.Shrinivaasan 22October2013
	*/
	/*
	if(sock)
	{
		sock_release(sock);
		printk(KERN_INFO "eventnet_log() : eventnet_log() client socket_release() invoked\n");
	}
	else
		printk(KERN_INFO "eventnet_log() : sock is NULL\n");
	*/

}
EXPORT_SYMBOL(virgo_eventnet_log);

static void __exit
virgo_generic_kernelsock_client_exit(void)
{
	printk(KERN_INFO "virgo_generic_kernelsock_client_exit(): exiting virgo cloud test kernel space module \n");
	do_exit(1);
}
EXPORT_SYMBOL(virgo_generic_kernelsock_client_exit);

MODULE_LICENSE("GPL");
module_init(virgo_generic_kernelsock_client_init);
module_exit(virgo_generic_kernelsock_client_exit);
