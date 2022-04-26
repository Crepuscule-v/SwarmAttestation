#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbc0f22cc, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x159d06c3, __VMLINUX_SYMBOL_STR(alloc_pages_current) },
	{ 0xcd65e4b1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x70296fb4, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x5fa2b608, __VMLINUX_SYMBOL_STR(ex_handler_fault) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xea7e81c5, __VMLINUX_SYMBOL_STR(crypto_alloc_shash) },
	{ 0x672edad8, __VMLINUX_SYMBOL_STR(pv_lock_ops) },
	{ 0xd5aef55a, __VMLINUX_SYMBOL_STR(boot_cpu_data) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x310020ad, __VMLINUX_SYMBOL_STR(__srcu_read_unlock) },
	{ 0xad27f361, __VMLINUX_SYMBOL_STR(__warn_printk) },
	{ 0xdba80fb4, __VMLINUX_SYMBOL_STR(__mmu_notifier_register) },
	{ 0x4e536271, __VMLINUX_SYMBOL_STR(__dynamic_pr_debug) },
	{ 0x778b8af3, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x1ca6c122, __VMLINUX_SYMBOL_STR(ex_handler_refcount) },
	{ 0x97651e6c, __VMLINUX_SYMBOL_STR(vmemmap_base) },
	{ 0xc46af633, __VMLINUX_SYMBOL_STR(set_page_dirty) },
	{ 0x54a62ac7, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x315a3d41, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xb44ad4b3, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x17de3d5, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xa084749a, __VMLINUX_SYMBOL_STR(__bitmap_or) },
	{ 0x21f0c5e2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xb33e4e1c, __VMLINUX_SYMBOL_STR(follow_pfn) },
	{ 0x574098a3, __VMLINUX_SYMBOL_STR(synchronize_srcu_expedited) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x104dbb0e, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xcfee476a, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0x8a3b82f5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3ca30931, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x863bb863, __VMLINUX_SYMBOL_STR(cleanup_srcu_struct) },
	{ 0x269ff28, __VMLINUX_SYMBOL_STR(mmu_notifier_unregister) },
	{ 0x67f189fe, __VMLINUX_SYMBOL_STR(apply_to_page_range) },
	{ 0x6bb80780, __VMLINUX_SYMBOL_STR(shmem_read_mapping_page_gfp) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xeb1051a3, __VMLINUX_SYMBOL_STR(crypto_shash_digest) },
	{ 0xb814e18a, __VMLINUX_SYMBOL_STR(on_each_cpu_mask) },
	{ 0x9e9fdd9d, __VMLINUX_SYMBOL_STR(memunmap) },
	{ 0x9c079d54, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe45d05a1, __VMLINUX_SYMBOL_STR(__srcu_read_lock) },
	{ 0x603f6942, __VMLINUX_SYMBOL_STR(radix_tree_next_chunk) },
	{ 0x8df92f66, __VMLINUX_SYMBOL_STR(memchr_inv) },
	{ 0xe007de41, __VMLINUX_SYMBOL_STR(kallsyms_lookup_name) },
	{ 0x8065a4fc, __VMLINUX_SYMBOL_STR(mmu_notifier_call_srcu) },
	{ 0xac43a688, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x1bbbf283, __VMLINUX_SYMBOL_STR(init_srcu_struct) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x811074cf, __VMLINUX_SYMBOL_STR(shmem_file_setup) },
	{ 0x663e265e, __VMLINUX_SYMBOL_STR(put_zone_device_private_or_public_page) },
	{ 0x7e880422, __VMLINUX_SYMBOL_STR(radix_tree_delete) },
	{ 0xf11543ff, __VMLINUX_SYMBOL_STR(find_first_zero_bit) },
	{ 0x7cd8d75e, __VMLINUX_SYMBOL_STR(page_offset_base) },
	{ 0x827476a3, __VMLINUX_SYMBOL_STR(find_vma) },
	{ 0x40a0fe83, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x23767f9d, __VMLINUX_SYMBOL_STR(mmu_notifier_unregister_no_release) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x8bcb743, __VMLINUX_SYMBOL_STR(get_user_pages) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xa202a8e5, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x2ea2c95c, __VMLINUX_SYMBOL_STR(__x86_indirect_thunk_rax) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0xcc199a6c, __VMLINUX_SYMBOL_STR(pv_cpu_ops) },
	{ 0x3239fd39, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xa8fa8fe2, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xec018b66, __VMLINUX_SYMBOL_STR(__radix_tree_insert) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0xe50cf061, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x56321ae2, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x310f02ec, __VMLINUX_SYMBOL_STR(memremap) },
	{ 0x426430cb, __VMLINUX_SYMBOL_STR(__radix_tree_next_slot) },
	{ 0x6337ebe6, __VMLINUX_SYMBOL_STR(synchronize_srcu) },
	{ 0xfe768495, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x237a015a, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xb5c5a27d, __VMLINUX_SYMBOL_STR(zap_vma_ptes) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb6849a14, __VMLINUX_SYMBOL_STR(pv_mmu_ops) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0x24f65409, __VMLINUX_SYMBOL_STR(fget) },
	{ 0xd4fa5c30, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x92a6f160, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0xa948e10, __VMLINUX_SYMBOL_STR(device_private_key) },
	{ 0x362ef408, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xe1cfed2, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0xb635ca36, __VMLINUX_SYMBOL_STR(__put_page) },
	{ 0x392eeef, __VMLINUX_SYMBOL_STR(vm_insert_pfn) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("acpi*:INT0E0C:*");

MODULE_INFO(srcversion, "0345E1AE1A9559F662312BF");
