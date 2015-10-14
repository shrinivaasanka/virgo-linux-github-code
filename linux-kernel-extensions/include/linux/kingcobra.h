/***************************************************************************************
KingCobra - BFT request servicing software on cloud with queues and arbiters

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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan, https://www.ohloh.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/


#ifndef _KINGCOBRA_H
#define _KINGCOBRA_H
 
#include <linux/string.h>
#include <linux/module.h>
#include <linux/virgo_queue.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/file.h>

#define KCOBRA_BUF_SIZE 512

struct file* request_reply_queue;

static int __init kingcobra_kernelspace_init(void);
static void __exit kingcobra_kernelspace_exit(void);
void kingcobra_servicerequest_kernelspace(void* args);

long parse_ip_address(char* request);
char* parse_timestamp(char* request);

void reply_to_publisher(long client_ip_l, char *response);

#endif
