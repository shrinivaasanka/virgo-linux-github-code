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
	{ 0xfa8ad6e7, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0xf0d24d50, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x333422b, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0x59e6046c, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x11a243dc, __VMLINUX_SYMBOL_STR(kernel_listen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xf994f3c6, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xbc35e2df, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0x7cdc799f, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x37c3e76, __VMLINUX_SYMBOL_STR(__gcov_merge_add) },
	{ 0x81c90249, __VMLINUX_SYMBOL_STR(push_request) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xe3fe0694, __VMLINUX_SYMBOL_STR(kingcobra_servicerequest_kernelspace) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xdceb3072, __VMLINUX_SYMBOL_STR(__gcov_init) },
	{ 0x46b5dae7, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x133375cb, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd93e4b5a, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0xe5034cb6, __VMLINUX_SYMBOL_STR(kernel_accept) },
	{ 0x5cbdbccf, __VMLINUX_SYMBOL_STR(virgo_cloud_test_kernelspace) },
	{ 0x8176a1e4, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0x90b89a28, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x3b8ce9df, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x6b7f0b64, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_queue,kingcobra_main_kernelspace,virgo_cloud_test_kernelspace";


MODULE_INFO(srcversion, "D49A3C636282480AA7BA164");
