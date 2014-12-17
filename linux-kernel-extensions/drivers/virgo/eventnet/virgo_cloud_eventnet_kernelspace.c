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
Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
--------------------------------------------------------------------------------------------------

*****************************************************************************************/


#include <linux/string.h>
#include <linux/module.h>
#include <linux/virgo_eventnet.h>
#include <linux/string.h>
#include <kstrtox.h>
#include <linux/ctype.h>

unsigned int virgo_parse_integer(const char *s, unsigned int base, unsigned long long *p);
void printBytes(const char* str);
char* toKernelAddress(const char*);
int toInteger(char*);
void virgo_cloud_eventnet_vertexmsg_kernelspace(struct virgo_eventnet_args*);
void virgo_cloud_eventnet_edgemsg_kernelspace(struct virgo_eventnet_args*);
struct virgo_eventnet_args* parse_virgofs_command_kernelspace(char* fsFunction);

static int __init
virgo_cloud_eventnet_kernelspace_init(void)
{
	printk(KERN_INFO "virgo_cloud_eventnet_kernelspace_init(): doing init() of virgo cloud kernel space test module and opening EventNet vertices and edges files in kernelspace\n");
        fs=get_fs();
        set_fs(get_ds());
        edgesf=filp_open("/var/log/eventnet/EventNetEdges.txt", O_RDWR|O_APPEND, 0);
        verticesf=filp_open("/var/log/eventnet/EventNetVertices.txt", O_RDWR|O_APPEND, 0);
	if(IS_ERR(verticesf) || IS_ERR(edgesf))
		printk(KERN_INFO "virgo_cloud_eventnet_kernelspace_init(): filp_open return value is error code : %p and %p", verticesf,edgesf);
	set_fs(fs);
	return 0;
}
EXPORT_SYMBOL(virgo_cloud_eventnet_kernelspace_init);


static void __exit
virgo_cloud_eventnet_kernelspace_exit(void)
{
	printk(KERN_INFO "virgo_cloud_eventnet_kernelspace_exit(): exiting virgo cloud test kernel space module \n");
	filp_close(verticesf,NULL);
	filp_close(edgesf,NULL);
	do_exit(1);
}
EXPORT_SYMBOL(virgo_cloud_eventnet_kernelspace_exit);


void virgo_cloud_eventnet_vertexmsg_kernelspace(struct virgo_eventnet_args* args)
{
	struct virgo_eventnet_args* vmargs=args;
	char *buf=kmalloc(sizeof(char)*500,GFP_KERNEL);
	sprintf(buf, "%s - %s - %s \n", vmargs->eventid_args[0],vmargs->eventid_args[1],vmargs->eventid_args[2]);
        fs=get_fs();
        set_fs(get_ds());
        vfs_write(verticesf, buf, sizeof(buf), &pos);
	set_fs(fs);
	pos+=sizeof(buf);
	return buf;
}
EXPORT_SYMBOL(virgo_cloud_eventnet_vertexmsg_kernelspace);



void virgo_cloud_eventnet_edgemsg_kernelspace(struct virgo_eventnet_args* args)
{
	struct virgo_eventnet_args* vmargs=args;
	char *buf=kmalloc(sizeof(char)*500,GFP_KERNEL);
	sprintf(buf, "%s,%s\n",vmargs->eventid_args[0],vmargs->eventid_args[1]);
        fs=get_fs();
        set_fs(get_ds());
        vfs_write(edgesf, buf, sizeof(buf), &pos);
	set_fs(fs);
	pos+=sizeof(buf);
	return NULL;
}
EXPORT_SYMBOL(virgo_cloud_eventnet_edgemsg_kernelspace);


void printBytes(const char* str)
{
	const char* p=str;
	while(*p != '\0')
	{
		printk(KERN_INFO "printBytes(): %c\n",*p);
		p++;
	}
	return;
}

/*
Carried over _parse_integer() from lib/kstrtox.c and modified for VIRGO by
adding an additional if clause for quote and unquote as below. 
Probably this missing clause could be causing the kstrtoll() and simple_strtoll()
which use _parse_integer() internally to randomly return junk addresses.
- Ka.Shrinivaasan 6November2013
*/
unsigned int virgo_parse_integer(const char *s, unsigned int base, unsigned long long *p)
{
	unsigned long long res;
	unsigned int rv;
	int overflow;

	res = 0;
	rv = 0;
	overflow = 0;
	while (*s) {
		printk(KERN_INFO "virgo_parse_integer(): *s=%c, res=%ld\n",*s, res);
		unsigned int val;
		if(*s=='\"')
		{
			s++;
			continue;
		}
		if ('0' <= *s && *s <= '9')
			val = *s - '0';
		else if ('a' <= tolower(*s) && tolower(*s) <= 'f')
			val = tolower(*s) - 'a' + 10;
		else
			break;

		if (val >= base)
			break;
		/*
		 * Check for overflow only if we are within range of
		 * it in the max base we support (16)
		if (unlikely(res & (~0ull << 60))) {
			if (res > div_u64(ULLONG_MAX - val, base))
				overflow = 1;
		}
		*/
		res = res * base + val;
		rv++;
		s++;
	}
	*p = res;
	return rv;
}

char* toVFSString(int* data)
{
        char* VFSString=kmalloc(BUF_SIZE, GFP_KERNEL);
        sprintf(VFSString,"%d",*data);
        printk(KERN_INFO "toVFSString(): VFSString=%s\n", VFSString);
        return VFSString;
}



MODULE_LICENSE("GPL");
module_init(virgo_cloud_eventnet_kernelspace_init);
module_exit(virgo_cloud_eventnet_kernelspace_exit);
