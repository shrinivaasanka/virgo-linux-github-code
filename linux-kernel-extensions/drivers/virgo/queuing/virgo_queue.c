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
Open Source Products Profile(Krishna iResearch): 
http://sourceforge.net/users/ka_shrinivaasan,
https://www.ohloh.net/accounts/ka_shrinivaasan 
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

/* 
	A standalone Queueing Driver implementation that can be used for VIRGO CPU and Memory pooling Drivers requests and  
	KingCobra byzantine request servicing pub-sub model
*/

#include <linux/virgo_queue.h>


static int __init virgo_queue_init()
{
	virgo_request_queue=kmalloc(VIRGO_QUEUE_SZ, GFP_KERNEL);
}

void push_request(struct virgo_request* req)
{
	virgo_request_queue[queue_end].data=kstrdup(req->data,GFP_KERNEL);
	virgo_request_queue[queue_end].next=req->next;
	queue_end++;
}

struct virgo_request* pop_request(struct virgo_request* req)
{
	return &virgo_request_queue[queue_front];
	queue_front++;
}

static void __exit virgo_queue_exit()
{
	do_exit(1);
}

MODULE_LICENSE("GPL");
module_init(virgo_queue_init);
module_exit(virgo_queue_exit);
