/***************************************************************************************
VIRGO - VIRtual Generic Os - linux kernel extensions for cloud 

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
Copyright(C):
Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
Independent Open Source Developer, Researcher and Consultant
Ph: 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

struct virgo_address
{
        int node_id;
        struct hostport* hstprt;
        void* addr;
};

struct hostport
{
        char* hostip;
        int port;
};


int main(int argc, char* argv[])
{

	/*
	virgo_malloc(), virgo_set(), virgo_get() and virgo_free() syscalls called by syscall numbers
	- Ka.Shrinivaasan
	*/

	struct virgo_address* vaddr;
	long long vaddr_longlong;
	/* virgo_malloc*/
	vaddr_longlong=syscall(351,1000,NULL,0,NULL);
	vaddr=(struct virgo_address*)vaddr_longlong;

	printf("test_virgo_malloc: vaddr_longlong = %u \n", vaddr_longlong);
	printf("test_virgo_malloc: VIRGO Address allocated on cloud by virgo_malloc() is vaddr = %p \n", vaddr);
	fflush(stdout);	

	/*
	/virgo_set/
	char* set_ret=(char*)syscall(352,vaddr,"test_virgo_malloc_data",NULL,0,NULL);
	if(set_ret)
		printf("set_ret = %s\n",set_ret);

	/virgo_get/
	char* get_ret=(char*)syscall(353,vaddr,NULL,0,NULL);
	if(get_ret)
		printf("get_ret = %s\n",get_ret);

	/virgo_free/
	char* free_ret=(char*)syscall(354,vaddr,NULL,0,NULL);
	/
	if(free_ret)
		printf("free_ret = %s\n",free_ret);
	/
	*/

	return 0;
}
