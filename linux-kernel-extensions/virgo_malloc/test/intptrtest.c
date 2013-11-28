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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct teststruct
{
	int i;
};

int main()
{
	struct teststruct *p3=(struct teststruct*)malloc(sizeof(struct teststruct));
	intptr_t sptr=(intptr_t)(void*)p3;
	int i=245;
	int *p=&i;
	intptr_t iptr=(intptr_t)(void*)p;
	printf("iptr=%u,sptr=%u\n",iptr,sptr);
	int *p2=(int *)iptr;
	struct teststruct *sptr2=(struct teststruct*)sptr;
	printf("p=%p, p2=%p, p3=%p,sptr2=%p\n",p,p2,p3,sptr);
	unsigned long x=0xf1481400;
	printf("x=%u, x=%x\n",x,x);
	const char* sptr5="test string";
	unsigned long sptr5ul=(unsigned long)sptr5;
	char* sptr6=(char*)sptr5ul;
	printf("sptr6=%s\n",sptr6);
}
