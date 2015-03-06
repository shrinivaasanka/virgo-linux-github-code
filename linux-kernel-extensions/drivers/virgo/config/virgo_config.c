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

#include <linux/virgo_config.h>
#include <linux/string.h>
#include <linux/kallsyms.h>


/*
Commented as of now so that each VIRGO module reads the config independently
- Ka.Shrinivaasan 17August2014

void read_virgo_config()
{
	/ virgo_cloud.conf contains a string of comma separated list of IP addresses in the virgo cloud .Read and strtok() it. /

	loff_t bytesread=0;
	loff_t pos=0;
	mm_segment_t fs;

	/
	  It is redundant to use kallsyms_lookup for exported symbols for virgo cloud initialization. 
	  kallsyms_lookup is for non-exported symbols.
	  
	  - Ka.Shrinivaasan 10 July 2013
	 

	node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("node_ip_addrs_in_cloud");
	num_cloud_nodes=kallsyms_lookup_name("num_cloud_nodes");

	printk(KERN_INFO "virgo config kernel service: read_virgo_config(): virgo_cloud config being read... \n");
	printk(KERN_INFO "virgo config kernel service: read_virgo_config(): num_cloud_nodes=%d #### node_ip_addrs_in_cloud=%s\n", num_cloud_nodes,node_ip_addrs_in_cloud);
	/

	fs=get_fs();
	set_fs(get_ds());
	struct file* f=NULL;
	f=filp_open("/etc/virgo_cloud.conf", O_RDONLY, 0);

	char buf[256];
	int i=0;

	int k=0;
	for(k=0;k<256;k++)
		buf[k]=0;

	for(k=0; k < num_cloud_nodes; k++)	
		printk(KERN_INFO "virgo kernel service: read_virgo_config(): before reading virgo_cloud.conf - virgo_cloud ip address - %d: %s\n", k+1, node_ip_addrs_in_cloud[k]);

	printk(KERN_INFO "read_virgo_config(): virgo_cloud config file being read \n");


	if(f !=NULL)
	{
		/f->f_op->read(f, buf, sizeof(buf), &f->f_pos);/
		bytesread=vfs_read(f, buf, 256, &pos);
		/strcpy(node_ip_addrs_in_cloud[i],buf);/
		printk(KERN_INFO "do_virgo_cloud_init(): virgo_cloud config file string of comma separated IPs : %s \n",buf);
		/printk(KERN_INFO "do_virgo_cloud_init(): virgo_cloud config file line %d \n",i);/
		pos=pos+bytesread;
	}
	/num_cloud_nodes=tokenize_list_of_ip_addrs(buf);/
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): %s\n",token);
		node_ip_addrs_in_cloud[i]=kstrdup(token,GFP_ATOMIC);
		printk(KERN_INFO "tokenize_list_of_ip_addrs(): node_ip_addrs_in_cloud[%d] = %s\n",i,node_ip_addrs_in_cloud[i]);
		i++;
	}
	num_cloud_nodes=i;
	set_fs(fs);
	filp_close(f,NULL);	
}
EXPORT_SYMBOL(read_virgo_config);
*/

/* 
Above tokenization made into a function - if needed can be used as multipurpose exported function
*/

/*
int tokenize_list_of_ip_addrs(char* buf)
{
	char* delim=",";
	char* token=NULL;
	char* bufdup=kstrdup(buf,GFP_ATOMIC);
	printk(KERN_INFO, "tokenize_list_of_ip_addrs(): bufdup = %s\n",bufdup);
	int i=0;
	while(bufdup != NULL)
	{
		token=strsep(&bufdup, delim);	
		printk(KERN_INFO, "tokenize_list_of_ip_addrs(): %s\n",token);
		/strcpy(node_ip_addrs_in_cloud[i],  token);/
		i++;
	}
	return i;
}
*/

static int __init
virgoconfig_init(void)
{
	printk(KERN_INFO "virgoconfig_init(): initializing virgo config kernel module \n");
	/*
	printk(KERN_INFO "virgoconfig_init(): invoking read_virgo_config()\n");
	read_virgo_config();
	*/
	int i=0;
	for(i=0; i < 10; i++)
        {
                printk(KERN_INFO "virgo_config_init() exported kernel_analytics variable: %s = %s \n",virgo_kernel_analytics_conf[i].key,virgo_kernel_analytics_conf[i].value);
        }

	return 0;
}
EXPORT_SYMBOL(virgoconfig_init);

static void __exit
virgoconfig_exit(void)
{
	printk(KERN_INFO "exiting virgo config kernel module \n");
	/*filp_close(file_stdout,NULL);*/
	do_exit(1);
}
EXPORT_SYMBOL(virgoconfig_exit);


MODULE_LICENSE("GPL");
module_init(virgoconfig_init);
module_exit(virgoconfig_exit);
