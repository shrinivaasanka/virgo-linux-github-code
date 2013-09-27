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
	{ 0xd320a490, "module_layout" },
	{ 0xa4724ca8, "kmalloc_caches" },
	{ 0xca14320f, "kernel_sendmsg" },
	{ 0xefbb6582, "sock_release" },
	{ 0xfed565f7, "filp_close" },
	{ 0x737cd06c, "sock_create_kern" },
	{ 0x85df9b6c, "strsep" },
	{ 0xa8513611, "kernel_listen" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x174b19cf, "kthread_create_on_node" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xc1cb6e28, "vfs_read" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x9a4e72a4, "kernel_sock_shutdown" },
	{ 0x952664c5, "do_exit" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4926b83d, "call_usermodehelper_fns" },
	{ 0xa05cd1bc, "wake_up_process" },
	{ 0xb3e96422, "kmem_cache_alloc_trace" },
	{ 0xeac115ce, "kernel_recvmsg" },
	{ 0x5065bcee, "kernel_accept" },
	{ 0x8195e7e2, "fd_install" },
	{ 0xe22acb2a, "kernel_bind" },
	{ 0xc89fbff6, "try_module_get" },
	{ 0xe914e41e, "strcpy" },
	{ 0xa21f5994, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B6700ABE59100BB496680F9");
