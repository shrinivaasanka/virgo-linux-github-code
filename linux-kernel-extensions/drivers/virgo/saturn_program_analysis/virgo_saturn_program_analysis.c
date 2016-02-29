/***************************************************************************************
#-------------------------------------------------------------------------------------------------------
#NEURONRAIN VIRGO - Cloud, Machine Learning and Queue augmented Linux Kernel Fork-off
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#--------------------------------------------------------------------------------------------------------
#Copyleft (Copyright+):
#Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
#Ph: 9791499106, 9003082186
#Krishna iResearch Open Source Products Profiles:
#http://sourceforge.net/users/ka_shrinivaasan,
#https://github.com/shrinivaasanka,
#https://www.openhub.net/accounts/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com,
#kashrinivaasan@live.com
#--------------------------------------------------------------------------------------------------------
*****************************************************************************************/

/*
	SATURN Program Analysis Tool Integration - http://saturn.stanford.edu
	Prerequisite: SATURN build and installation with NATIVE OCAML unset, OCAML and LibStr libraries dependencies.
*/ 

#include <linux/virgo_kernel_analytics.h>
#include <linux/string.h>
#include <linux/kallsyms.h>


void read_virgo_kernel_analytics_config()
{
	/* virgo_kernel_analytics.conf contains key-value pairs of kernel analytics variables set by AsFer machine learning and analytics code. */

	loff_t bytesread=0;
	loff_t pos=0;
	mm_segment_t fs;

	/*
	  It is redundant to use kallsyms_lookup for exported symbols for virgo cloud initialization. 
	  kallsyms_lookup is for non-exported symbols.
	  
	  - Ka.Shrinivaasan 10 July 2013
	 

	node_ip_addrs_in_cloud=(char**)kallsyms_lookup_name("node_ip_addrs_in_cloud");
	num_cloud_nodes=kallsyms_lookup_name("num_cloud_nodes");

	*/

	printk(KERN_INFO "virgo kernel_analytics kernel service: read_virgo_kernel_analytics(): virgo_cloud kernel_analytics being read... \n");
	fs=get_fs();
	set_fs(get_ds());
	struct file* f=NULL;
	f=filp_open("/etc/virgo_kernel_analytics.conf", O_RDONLY, 0);

	if(IS_ERR(f))
		printk(KERN_INFO, "read_virgo_kernel_analytics(): error opening virgo_kernel_analytics.conf");

	char buf[3000];
	int i=0;

	int k=0;
	for(k=0;k<256;k++)
		buf[k]=0;

	printk(KERN_INFO "read_virgo_kernel_analytics(): virgo_cloud kernel_analytics file being read \n");

	char* key;
	char* value;
	/*
	while(bytesread=vfs_read(f, buf, 256, &pos))
	{
		printk(KERN_INFO "===========================================");
		printk(KERN_INFO "read_virgo_kernel_analytics(): virgo_cloud kernel_analytics file line %d \n",i);
		char* delim="=";
		char* bufdup=kstrdup(buf,GFP_ATOMIC);
		printk(KERN_INFO "read_virgo_kernel_analytics(): bufdup = %s\n",bufdup);
		virgo_kernel_analytics_conf[i].key=kstrdup(strsep(&bufdup, delim),GFP_ATOMIC);	
		printk(KERN_INFO "read_virgo_kernel_analytics(): key = %s\n",key);
		virgo_kernel_analytics_conf[i].value=kstrdup(bufdup,GFP_ATOMIC);
		printk(KERN_INFO "read_virgo_kernel_analytics(): value = %s\n",value);
		pos=pos+bytesread;
		i++;
	}
	*/

	pos=0;
        if(f !=NULL)
        {
                bytesread=vfs_read(f, buf, 3000, &pos);
                pos=pos+bytesread;
        }
        char* confdelim=",";
	char* keyvaluedelim="=";
        char* confvar=NULL;
        char* bufdup=kstrdup(buf,GFP_KERNEL);
        while(bufdup != NULL)
        {
                confvar=strsep(&bufdup, confdelim);
		char* confvardup=kstrdup(confvar,GFP_ATOMIC);
		char* confkey=strsep(&confvardup, keyvaluedelim);
		char* confvalue=confvardup;	
                virgo_kernel_analytics_conf[i].key=kstrdup(confkey,GFP_KERNEL);
                virgo_kernel_analytics_conf[i].value=kstrdup(confvalue,GFP_KERNEL);
		printk(KERN_INFO "read_virgo_kernel_analytics_config() parsed analytics variable: %s = %s \n",virgo_kernel_analytics_conf[i].key,virgo_kernel_analytics_conf[i].value);
                i++;
        }

	set_fs(fs);
	filp_close(f,NULL);	
}
EXPORT_SYMBOL(read_virgo_kernel_analytics_config);


static int __init
virgosaturn_program_analysis_init(void)
{
	printk(KERN_INFO "virgosaturn_program_analysis_init(): initializing virgo kernel_analytics kernel module \n");
	printk(KERN_INFO "virgosaturn_program_analysis_init(): invoking read_virgo_kernel_analytics()\n");
	read_virgo_kernel_analytics_config();

	return 0;
}
EXPORT_SYMBOL(virgosaturn_program_analysis_init);

static void __exit
virgosaturn_program_analysis_exit(void)
{
	printk(KERN_INFO "exiting virgo saturn program analysis kernel module \n");
	/*filp_close(file_stdout,NULL);*/
	do_exit(1);
}
EXPORT_SYMBOL(virgosaturn_program_analysis_exit);


MODULE_LICENSE("GPL");
module_init(virgosaturn_program_analysis_init);
module_exit(virgosaturn_program_analysis_exit);
