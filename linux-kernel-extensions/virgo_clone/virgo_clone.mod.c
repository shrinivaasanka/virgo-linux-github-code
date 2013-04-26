#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x36c33dd0, "module_layout" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xafd83fbb, "kernel_recvmsg" },
	{ 0xc77614ca, "kernel_sendmsg" },
	{ 0xb3b722e9, "kernel_connect" },
	{ 0x140b3257, "sock_create" },
	{ 0xe914e41e, "strcpy" },
	{ 0xaccabc6a, "in4_pton" },
	{ 0xd0d8621b, "strlen" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x2ed2c4e4, "kmem_cache_alloc_trace" },
	{ 0xfaae8f6e, "kmalloc_caches" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "37C2B2AC5AD0AA2B9763138");
