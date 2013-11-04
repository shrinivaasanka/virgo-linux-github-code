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
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x20000329, "simple_strtoul" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x50eedeb8, "printk" },
	{ 0x20c55ae0, "sscanf" },
	{ 0xb4390f9a, "mcount" },
	{ 0x952664c5, "do_exit" },
	{ 0x54a9db5f, "_kstrtoul" },
	{ 0x37a0cba, "kfree" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2555E82C2236B7AAC7294E1");
