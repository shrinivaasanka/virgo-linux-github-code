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
	{ 0x43a53735, "__alloc_workqueue_key" },
	{ 0x92c90e22, "queue_work" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x952664c5, "do_exit" },
	{ 0x86a4889a, "kmalloc_order_trace" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "61C75E84637FF817B5B7E37");
