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
	{ 0x5ac9bae1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x649c402a, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x405c1144, __VMLINUX_SYMBOL_STR(get_seconds) },
	{ 0x4c4fef19, __VMLINUX_SYMBOL_STR(kernel_stack) },
	{ 0x94768c77, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0x19587802, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x20bbf85b, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0x2b701874, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0xc198e6ed, __VMLINUX_SYMBOL_STR(kernel_listen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x6d1a33c1, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xf32ddb91, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0x3670f60c, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x189f8038, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x702984bb, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x42f8b31d, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0x52a5c2ab, __VMLINUX_SYMBOL_STR(kernel_accept) },
	{ 0x5cbdbccf, __VMLINUX_SYMBOL_STR(virgo_cloud_test_kernelspace) },
	{ 0xd7d3f891, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0xaf5069f5, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0xcc547fac, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xd5b3be9f, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_cloud_test_kernelspace";


MODULE_INFO(srcversion, "A0150F3E58F60B5547F60B6");
