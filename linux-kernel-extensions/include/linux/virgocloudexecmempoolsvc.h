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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#ifndef _LINUX_VIRGOCLOUDEXECMEMPOOLSVC_H
#define _LINUX_VIRGOCLOUDEXECMEMPOOLSVC_H

#include <linux/virgo_mempool.h>
#include <linux/socket.h>


int virgo_cloudexec_mempool_service(void* args)
{

	try_module_get(virgo_mempool_class.m_virgo_owner);
	while(1)
	{
		printk(KERN_INFO "virgo_cloudexec_mempool_service(): virgo_mempool_ops.virgo_create() \n");
		struct socket* clsock = virgo_mempool_ops.virgo_mempool_create();

		/*
		Multithreaded VIRGO Memory Pooling Kernel Service
		-------------------------------------------------
		*/
		
		
		struct task_struct *task;
		void* args=clsock;
		int woken_up=0;
		printk(KERN_INFO "virgo_cloudexec_mempool_service(): virgo mempool client thread per request \n");
                task=kthread_create(virgo_mempool_client_thread, (void*)args, "virgo memorypool client thread per virgo_clone request");
		woken_up=wake_up_process(task);

		/*
		virgo_ops.virgo_recvfrom();
		virgo_ops.virgo_sendto();
		*/
	}

}

/*
Multithreaded VIRGO Memory Pooling Kernel Service
-------------------------------------------------
*/

int virgo_mempool_client_thread(void* args)
{
		struct socket* clientsock=(struct socket*)args;
		printk(KERN_INFO "virgo_mempool_client_thread(): virgo_mempool_ops.virgo_mempool_recvfrom()\n");
		virgo_mempool_ops.virgo_mempool_recvfrom(clientsock);
		printk(KERN_INFO "virgo_mempool_client_thread(): virgo_mempool_ops.virgo_mempool_sendto()\n");
		virgo_mempool_ops.virgo_mempool_sendto(clientsock);
}

#endif
