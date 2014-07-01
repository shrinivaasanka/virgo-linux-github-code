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
Ph: 9789346927, 9003082186, 9791165980
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan, http://www.ohloh.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>


struct hostport
{
        char* hostip;
        int port;
};


int main(int argc, char* argv[])
{
	/*
	Testcases for:

	sys_virgo_open(char* filepath);
	sys_virgo_read(long vfsdesc, char __user *data_out, int size, int pos);
	sys_virgo_write(long vfsdesc, const char __user *data_in, int size, int pos);
	sys_virgo_close(long vfsdesc);

	invoked by syscall numbers in arch/x86/syscalls/syscalls_32.tbl
	*/

	long vfsdesc = syscall(355,"./virgofstext.txt"); /* open */
	char data_read[256];
	syscall(357,vfsdesc,data_read,100,0); /* read */
	syscall(358,vfsdesc,"test_virgo_filesystem",100,100);/* write */
	syscall(356,vfsdesc); /* close */
	return 0;
}
