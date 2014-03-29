#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x8a9dc593, "module_layout" },
	{ 0xb1278c61, "kmalloc_caches" },
	{ 0x4f84ad10, "kernel_sendmsg" },
	{ 0xd3fc9f1a, "sock_release" },
	{ 0x143054c, "filp_close" },
	{ 0x794f5965, "sock_create_kern" },
	{ 0x85df9b6c, "strsep" },
	{ 0xe72a3ab3, "kernel_listen" },
	{ 0x91715312, "sprintf" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0xfa336f83, "kthread_create_on_node" },
	{ 0xbdb1002f, "vfs_read" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xf8a4b0e5, "kernel_sock_shutdown" },
	{ 0x64c0ec, "num_cloud_nodes" },
	{ 0x952664c5, "do_exit" },
	{ 0x81c90249, "push_request" },
	{ 0x61651be, "strcat" },
	{ 0xfe26f191, "node_ip_addrs_in_cloud" },
	{ 0xe3fe0694, "kingcobra_servicerequest_kernelspace" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x68d4fad5, "call_usermodehelper_fns" },
	{ 0x281056ca, "wake_up_process" },
	{ 0xac518073, "kmem_cache_alloc_trace" },
	{ 0xd206e501, "kernel_recvmsg" },
	{ 0x40b508a5, "kernel_accept" },
	{ 0x5cbdbccf, "virgo_cloud_test_kernelspace" },
	{ 0x8286aacc, "fd_install" },
	{ 0xaa099fde, "kernel_bind" },
	{ 0x1616a37c, "try_module_get" },
	{ 0xe914e41e, "strcpy" },
	{ 0x95a608a3, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_queue,kingcobra_main_kernelspace,virgo_cloud_test_kernelspace";


MODULE_INFO(srcversion, "D49A3C636282480AA7BA164");
