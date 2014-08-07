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
	{ 0x1b24d8b0, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xabcda7ae, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x4c4fef19, __VMLINUX_SYMBOL_STR(kernel_stack) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x333422b, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x37c3e76, __VMLINUX_SYMBOL_STR(__gcov_merge_add) },
	{ 0xe3fe0694, __VMLINUX_SYMBOL_STR(kingcobra_servicerequest_kernelspace) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xdceb3072, __VMLINUX_SYMBOL_STR(__gcov_init) },
	{ 0x133375cb, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6b7f0b64, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=kingcobra_main_kernelspace";


MODULE_INFO(srcversion, "95D8EF1D4CDEBDFB114F725");
