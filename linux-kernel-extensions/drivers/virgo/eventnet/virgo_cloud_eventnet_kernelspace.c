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
Ph: 9789346927, 9003082186, 9791165980
Krishna iResearch Open Source Products Profiles: 
http://sourceforge.net/users/ka_shrinivaasan, https://www.openhub.net/accounts/ka_shrinivaasan
Personal website(research): https://sites.google.com/site/kuja27/
ZODIAC DATASOFT: https://github.com/shrinivaasanka/ZodiacDatasoft
emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, 
kashrinivaasan@live.com
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
        edgesf=filp_open("/var/log/eventnet/EventNetEdges.txt", O_RDWR | O_CREAT | O_APPEND | O_LARGEFILE , 0777);
        verticesf=filp_open("/var/log/eventnet/EventNetVertices.txt", O_RDWR | O_CREAT | O_LARGEFILE , 0777);
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
	loff_t readpos=0;
	int vertexexists=0;
        fs=get_fs();
        set_fs(get_ds());
	struct virgo_eventnet_args* vmargs=args;
	char *buf=kmalloc(sizeof(char)*500,GFP_ATOMIC);
	char *readbuf=kmalloc(sizeof(char)*500,GFP_ATOMIC);
	loff_t prevreadpos=0;
	while(1)
	{
		prevreadpos=readpos;
		vfs_read(verticesf, readbuf, 500, &readpos); 
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): readbuf = %s\n", readbuf);
		char* readbuf_dup=kstrdup(readbuf,GFP_ATOMIC);
		char* strsep_eventid=kstrdup(strsep(&readbuf_dup,"-"), GFP_ATOMIC);
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): vmargs->event_id = %s, strsep_eventid = %s\n", vmargs->event_id, strsep_eventid);
		/*if((strsep_eventid != NULL) && (strcmp(strsep_eventid,vmargs->event_id)==0))*/
		unsigned long long x1;
		unsigned long long x2;

		/*
			strcmp() is sufficient but mysteriously fails, hence using virgo_parse_integer() with
			bugfix done for VIRGO Linux Kernel.
		*/
		virgo_parse_integer(vmargs->event_id,10,&x1);
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): x1=%ld\n",x1);
		virgo_parse_integer(strsep_eventid,10,&x2);
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): x2=%ld\n",x2);
		if(x1==x2)
		{
			vertexexists=1;
			break;
		}
		readpos+=strlen(readbuf);
	}
	char* event_id=kstrdup(strsep(&readbuf,"-"),GFP_ATOMIC);
	char* partakers=kstrdup(strsep(&readbuf,"-"),GFP_ATOMIC);
	char* conversations=kstrdup(readbuf,GFP_ATOMIC); 

	if(vertexexists)
	{
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): vertex exists in kernel storage");
		sprintf(buf, "%s - %s,%s,%s - %s#(%s,%s)\n", event_id, partakers, vmargs->eventid_args[0],vmargs->eventid_args[1], conversations, vmargs->eventid_args[0], vmargs->eventid_args[1]);
	}
	else
	{
		printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): new vertex in kernel storage");
		sprintf(buf, "%s - %s,%s - (%s,%s)\n", readbuf,vmargs->eventid_args[0],vmargs->eventid_args[1]);
	}
		
	printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): prevreadpos=%d, readpos=%d without subtraction for readbuf\n",prevreadpos, readpos);
        int ret = vfs_write(verticesf, buf, strlen(buf)+1, &prevreadpos);
	printk(KERN_INFO "virgo_cloud_eventnet_vertexmsg_kernelspace(): prevreadpos=%d, readpos=%d, vfs_write() ret value = %d\n",prevreadpos, readpos, ret);
	set_fs(fs);
}
EXPORT_SYMBOL(virgo_cloud_eventnet_vertexmsg_kernelspace);


void virgo_cloud_eventnet_edgemsg_kernelspace(struct virgo_eventnet_args* args)
{
	struct virgo_eventnet_args* vmargs=args;
	char *buf=kmalloc(sizeof(char)*500,GFP_ATOMIC);
	sprintf(buf, "%s,%s\n",vmargs->eventid_args[0],vmargs->eventid_args[1]);
        fs=get_fs();
        set_fs(get_ds());
        vfs_write(edgesf, buf, strlen(buf)+1, &pos);
	set_fs(fs);
	pos+=strlen(buf);
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
        char* VFSString=kmalloc(BUF_SIZE, GFP_ATOMIC);
        sprintf(VFSString,"%d",*data);
        printk(KERN_INFO "toVFSString(): VFSString=%s\n", VFSString);
        return VFSString;
}



MODULE_LICENSE("GPL");
module_init(virgo_cloud_eventnet_kernelspace_init);
module_exit(virgo_cloud_eventnet_kernelspace_exit);
