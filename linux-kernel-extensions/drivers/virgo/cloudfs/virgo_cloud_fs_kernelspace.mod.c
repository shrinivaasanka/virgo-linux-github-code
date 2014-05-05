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
	{ 0x143054c, "filp_close" },
	{ 0x91715312, "sprintf" },
	{ 0xbdb1002f, "vfs_read" },
	{ 0x11089ac7, "_ctype" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x952664c5, "do_exit" },
	{ 0xac518073, "kmem_cache_alloc_trace" },
	{ 0x51bd0a05, "vfs_write" },
	{ 0x95a608a3, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "12432E5390F77890E781873");
