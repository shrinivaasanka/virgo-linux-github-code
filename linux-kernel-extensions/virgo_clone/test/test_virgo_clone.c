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

#include <stdio.h>
/*#include <linux/kernel.h>*/
#include <syscall.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	/*
	long int ret=syscall(350,"int clone_func(void* args)",NULL,0,NULL);
	*/

	/*
	Mangled name for function prototype "void* virgo_cloud_test(void*)" is sent to virgo_cloudexec kernel service which does
	upcall to userspace to invoke the function (within libvirgo.so) in remote cloud node. Kernel upcall usermode helper 
	requires mangled names for dlsym(). This also is a unique id for a function. Library libvirgo.so needs to be prebuilt
	with all functions that need to be on cloud and should be replicated in all cloud nodes.
	For executable parameter, complete path to binary is passed in.
	\r\n or " " padded is stripped off by kernel recv code in virgo_cloudexec by strsep tokenizer. It is intriguing that telnet 
	connection works without any padding.

	- Ka.Shrinivaasan
	*/


	long int ret=syscall(359,"virgo_cloud_test_kernelspace ");
	/*long int ret=syscall(350,"_Z16virgo_cloud_testPv ",NULL,0,NULL);*/
	/*long int ret=syscall(350,"/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/virgo_cloud_test_main ",NULL,0,NULL);*/
	/*long int ret=syscall(350,argv[1],NULL,0,NULL);*/
	return 0;
}
