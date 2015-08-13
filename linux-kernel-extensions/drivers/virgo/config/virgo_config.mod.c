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
	{ 0x86983313, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x69e59c53, __VMLINUX_SYMBOL_STR(virgo_kernel_analytics_conf) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_kernel_analytics";


MODULE_INFO(srcversion, "D380C114EBE48DB71977D63");
