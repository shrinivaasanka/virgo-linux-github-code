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
	{ 0x405c1144, __VMLINUX_SYMBOL_STR(get_seconds) },
	{ 0x4c4fef19, __VMLINUX_SYMBOL_STR(kernel_stack) },
	{ 0x11ff7079, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0xafc5ef70, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0xd331fcb4, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xc799b2af, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x345e1ef, __VMLINUX_SYMBOL_STR(kernel_listen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x2339bde6, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x5bbc998e, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0xe70b5938, __VMLINUX_SYMBOL_STR(kernel_sock_shutdown) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xe3fe0694, __VMLINUX_SYMBOL_STR(kingcobra_servicerequest_kernelspace) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x27d5206a, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xa4c996c2, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x162062c, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0x1d43f511, __VMLINUX_SYMBOL_STR(kernel_accept) },
	{ 0x8e4d8bf8, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6a033706, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xbfc1f223, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=kingcobra_main_kernelspace";


MODULE_INFO(srcversion, "43A3391BC28AEFB6466E71D");
