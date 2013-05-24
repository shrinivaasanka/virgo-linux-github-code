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
	{ 0x4f84ad10, "kernel_sendmsg" },
	{ 0x794f5965, "sock_create_kern" },
	{ 0xe72a3ab3, "kernel_listen" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0xfa336f83, "kthread_create_on_node" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x952664c5, "do_exit" },
	{ 0xd206e501, "kernel_recvmsg" },
	{ 0x40b508a5, "kernel_accept" },
	{ 0xaa099fde, "kernel_bind" },
	{ 0x1616a37c, "try_module_get" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B7656F553F07868AECB7A5A");
