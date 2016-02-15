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
	{ 0xf23db2b3, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x405c1144, __VMLINUX_SYMBOL_STR(get_seconds) },
	{ 0xb855372e, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x139b504, __VMLINUX_SYMBOL_STR(cpu_current_top_of_stack) },
	{ 0xb3ac8151, __VMLINUX_SYMBOL_STR(virgo_cloud_set_kernelspace) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0xbb66ad9f, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0xcd998398, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0x187aff44, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0xde40fc2b, __VMLINUX_SYMBOL_STR(kernel_listen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x69e59c53, __VMLINUX_SYMBOL_STR(virgo_kernel_analytics_conf) },
	{ 0x9aab63c, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x39506191, __VMLINUX_SYMBOL_STR(virgo_cloud_get_kernelspace) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x9cc701b9, __VMLINUX_SYMBOL_STR(virgo_cloud_malloc_kernelspace) },
	{ 0xcd4572ea, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0x6c2e3320, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0x2175cb1, __VMLINUX_SYMBOL_STR(virgo_cloud_free_kernelspace) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x13f168f2, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x86c90730, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2fa31741, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0x74210458, __VMLINUX_SYMBOL_STR(kernel_accept) },
	{ 0x8e123c5c, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0x97b50f7b, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x8a85c29e, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x1085e609, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=virgo_cloud_mempool_kernelspace,virgo_kernel_analytics";


MODULE_INFO(srcversion, "2CD655873C9D37CA90E4AD8");
