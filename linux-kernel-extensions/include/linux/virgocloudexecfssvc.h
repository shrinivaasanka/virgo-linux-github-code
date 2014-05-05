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
Ph: 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan, http://ohloh.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#ifndef _LINUX_VIRGOCLOUDEXECMEMPOOLSVC_H
#define _LINUX_VIRGOCLOUDEXECMEMPOOLSVC_H

#include <linux/virgo_fs.h>
#include <linux/socket.h>


int virgo_cloudexec_fs_service(void* args)
{

	try_module_get(virgo_fs_class.m_virgo_owner);
	while(1)
	{
		printk(KERN_INFO "virgo_cloudexec_fs_service(): virgo_fs_ops.virgo_create() \n");
		struct socket* clsock = virgo_fs_ops.virgo_fs_create();

		/*
		Multithreaded VIRGO File System Kernel Service
		-------------------------------------------------
		*/
		
		
		struct task_struct *task;
		void* args=clsock;
		int woken_up=0;
		printk(KERN_INFO "virgo_cloudexec_fs_service(): virgo fs client thread per request \n");
                task=kthread_create(virgo_fs_client_thread, (void*)args, "virgo fs client thread per virgo_fs syscall request");
		woken_up=wake_up_process(task);

		/*
		virgo_ops.virgo_recvfrom();
		virgo_ops.virgo_sendto();
		*/
	}

}

/*
Multithreaded VIRGO File System Kernel Service
-------------------------------------------------
*/

int virgo_fs_client_thread(void* args)
{
		/*mutex_lock(&virgo_fs_mutex);*/
		struct socket* clientsock=(struct socket*)args;
		printk(KERN_INFO "virgo_fs_client_thread(): virgo_fs_ops.virgo_fs_recvfrom()\n");
		char *virgo_fs_ret=(char*)virgo_fs_ops.virgo_fs_recvfrom(clientsock);
		printk(KERN_INFO "virgo_fs_client_thread(): virgo_fs_ops.virgo_fs_sendto()\n");
		virgo_fs_ops.virgo_fs_sendto(clientsock, virgo_fs_ret);
		/*mutex_unlock(&virgo_fs_mutex);*/
}

#endif
