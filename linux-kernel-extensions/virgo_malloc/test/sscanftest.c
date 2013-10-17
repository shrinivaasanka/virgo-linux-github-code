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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/*

userspace sscanf and vsscanf %p modifier testcase

Outputs:
--------
kashrinivaasan@kashrinivaasan-Inspiron-1545:~/linux-3.7.8/virgo_malloc/test$ ./sscanftest 
p=0x80486d0, str after sprintf: [0x80486d0]
str=[0x80486d0], p2 after sscanf: 0x80486d0 
after var_sscanf(): str=[0x80486d0], p2 after sscanf: 0x80486d0 

similar sscanf() works for kernel space in virgo_cloud_mempool_kernelspace.ko 
but doesn't work in virgo_malloc.c and returns null

*/


void var_sscanf(char *str, const char* fmt, ...);

int main()
{
	const char* p="string";
	void* p2;
	char str[300];
	sprintf(str, "%p", p);
	printf("p=%p, str after sprintf: [%s]\n", p, str);
	sscanf(str, "%p", (void**)&p2);
	printf("str=[%s], p2 after sscanf: %p \n", str, p2);
	var_sscanf(str, "%p", (void**)&p2);
	printf("after var_sscanf(): str=[%s], p2 after sscanf: %p \n", str, p2);
	return 0;
}

void var_sscanf(char *str, const char* fmt, ...)
{
	va_list vargs;
	va_start(vargs, fmt);
	vsscanf(str, fmt, vargs);
	va_end(vargs);
}
	
