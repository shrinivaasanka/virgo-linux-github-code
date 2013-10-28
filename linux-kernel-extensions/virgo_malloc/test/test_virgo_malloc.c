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
	long long virgo_unique_id;
	/* virgo_malloc*/
	syscall(351,1000,&virgo_unique_id,NULL,0,NULL);
	vaddr=(struct virgo_address*)virgo_unique_id;

	printf("test_virgo_malloc: virgo_unique_id = %u \n", virgo_unique_id);
	printf("test_virgo_malloc: VIRGO Address obtained by struct virgo_address*, vaddr = %p \n", vaddr);
	fflush(stdout);	

	/*virgo_set*/
	char* set_data="test_virgo_malloc_data";
	long long set_ret=syscall(352,virgo_unique_id,set_data,NULL,0,NULL);
	printf("set_ret = %ld\n",set_ret);
	fflush(stdout);	

	/*virgo_get*/
	char* get_data;
	long long get_ret=syscall(353,virgo_unique_id,get_data,NULL,0,NULL);
	if(get_data)
		printf("get_ret = %s\n",get_data);
	fflush(stdout);	

	/*virgo_free*/
	long long free_ret=syscall(354,virgo_unique_id,NULL,0,NULL);
	printf("free_ret = %ld\n",free_ret);
	fflush(stdout);	

	return 0;
}
