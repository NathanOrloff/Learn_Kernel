#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/kernel.h>

/* Defines */
#define NAME "chardev"

/* Meta information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nathan Orloff");
MODULE_DESCRIPTION("echo user input to the kmsg");

/* Prototypes */
static int __init ModuleInit(void);
static void __exit ModuleExit(void);
static ssize_t write(struct file *file, const char *buf, size_t count, loff_t *pos);

/* Global Variables */
static struct proc_ops fops = {
	.proc_write = write
};
struct proc_dir_entry *entry;

/**
 * @brief init function for module 
 * */
static int __init ModuleInit(void) {
	entry = proc_create(NAME, 0222, NULL, &fops);
	if (!entry) {
		printk(KERN_INFO "failed to create proc file");
		return -ENOENT;
	}
	printk(KERN_INFO "proc module init successfully");
	return 0;
}

/**
 * @brief exit function for module
 * */
static void __exit ModuleExit(void) {
	proc_remove(entry);
	printk(KERN_INFO "proc module exited successfully");
}


/**
 * @brief write function for module, writes message to kmsg
 * */
static ssize_t write(struct file *file, const char *buf, size_t count, loff_t *pos){
	char text[255];
	int to_copy, not_copied, delta;

	/* clear text */
	memset(text, 0, sizeof(text));

	/* get amount to copy */
	to_copy = min(count, sizeof(text));

	/* copy data to user */
	not_copied = copy_from_user(text, buf, to_copy);
	printk(KERN_INFO "%s\n", text);

	/* calculate data */
	delta = to_copy - not_copied;
	return delta;
}

module_init(ModuleInit);
module_exit(ModuleExit);

