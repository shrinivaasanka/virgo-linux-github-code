#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0xce128e84, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x4febffce, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2339bde6, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x27d5206a, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xa4c996c2, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "51C535A7A3E4793EF2CD15D");