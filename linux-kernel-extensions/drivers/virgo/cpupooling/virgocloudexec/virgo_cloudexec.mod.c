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
	{ 0x36c33dd0, "module_layout" },
	{ 0xc77614ca, "kernel_sendmsg" },
	{ 0xe914e41e, "strcpy" },
	{ 0xfa336f83, "kthread_create_on_node" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0xafd83fbb, "kernel_recvmsg" },
	{ 0x781ef3c4, "kernel_accept" },
	{ 0xbb54f3af, "kernel_listen" },
	{ 0xcb894ad1, "kernel_bind" },
	{ 0x140b3257, "sock_create" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x952664c5, "do_exit" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "14C355A4A8124E800F8A3CC");
