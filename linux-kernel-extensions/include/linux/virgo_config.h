#ifndef _VIRGO_CONFIG_H_
#define _VIRGO_CONFIG_H_

#include <linux/ioport.h>
#include <linux/kobject.h>
#include <linux/klist.h>
#include <linux/list.h>
#include <linux/lockdep.h>
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/pm.h>
#include <linux/atomic.h>
#include <linux/ratelimit.h>
#include <asm/device.h>

/******************************************/

#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/file.h>
#include <linux/freezer.h>
#include <net/sock.h>
#include <net/checksum.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/tcp.h>
#include <net/tcp_states.h>
#include <asm/uaccess.h>
#include <asm/ioctls.h>
#include <trace/events/skb.h>

#include <linux/module.h>
#include <linux/types.h>
#include <linux/uio.h>
#include <linux/unistd.h>
/*#include <linux/init.h>*/

#include <linux/sunrpc/types.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sunrpc/xdr.h>
#include <linux/sunrpc/msg_prot.h>
#include <linux/sunrpc/svcsock.h>
#include <linux/sunrpc/stats.h>
#include <linux/sunrpc/xprt.h>
/*#include "sunrpc.h"*/
#include <linux/sunrpc/xprt.h>
/*#include "netns.h"*/


int virgocpupooling_num_cloud_nodes;
char* virgocpupooling_node_ip_addrs_in_cloud[3000];

int virgomemorypooling_num_cloud_nodes;
char* virgomemorypooling_node_ip_addrs_in_cloud[3000];

int virgofs_num_cloud_nodes;
char* virgofs_node_ip_addrs_in_cloud[3000];

char* virgoeventnet_node_ip_addrs_in_cloud[3000];
int virgoeventnet_num_cloud_nodes;

#define MAX_ANALYTICS_CONF 500

struct virgo_kernel_analytics_config
{
        char* key;
        char* value;
};

extern struct virgo_kernel_analytics_config virgo_kernel_analytics_conf[MAX_ANALYTICS_CONF];

#endif
