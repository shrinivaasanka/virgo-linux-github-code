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
	{ 0x11c92bdf, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7f457a3b, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x22583a00, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0xf23d7be8, __VMLINUX_SYMBOL_STR(sock_release) },
	{        0, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xe0c47565, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0xa215ded, __VMLINUX_SYMBOL_STR(kernel_listen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x13d191b5, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xeab4ff9a, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0xffc62ac7, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x81c90249, __VMLINUX_SYMBOL_STR(push_request) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xe3fe0694, __VMLINUX_SYMBOL_STR(kingcobra_servicerequest_kernelspace) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x88050b1e, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xd3813bef, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37124cc9, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0x5373ad06, __VMLINUX_SYMBOL_STR(kernel_accept) },
	{ 0x5cbdbccf, __VMLINUX_SYMBOL_STR(virgo_cloud_test_kernelspace) },
	{ 0xa254623c, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0x152f271a, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x9f82716e, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xdb18b84e, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_queue,kingcobra_main_kernelspace,virgo_cloud_test_kernelspace";


MODULE_INFO(srcversion, "D49A3C636282480AA7BA164");
