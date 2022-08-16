// 最基本的两个头文件
#include <linux/module.h>
#include <linux/init.h>

#include <linux/fs.h> // 字符型设备驱动注册函数头文件
#include <linux/slab.h>
#include <linux/device.h>

#include "char_mem_dev_cmd.h"
// 入参（默认值）
static char *name = "Guo";
static int num = 1000;

struct CharMemoryDev {
	int major;
	struct class *class;
	struct device *device;
	int size;
	char *mem;
};
static struct CharMemoryDev *chrdev = NULL;

#define DEVICE_NAME		"char_mem_dev"

static int char_mem_open(struct inode *node, struct file *file)
{
	if (chrdev->mem == NULL) {
		chrdev->mem = (char*)kzalloc(num * sizeof(char), GFP_KERNEL);
		chrdev->size = num;
	}
	file->private_data = chrdev;
	return 0;
}

static int char_mem_release(struct inode *node, struct file *file)
{
	struct CharMemoryDev *c = file->private_data;
	kfree(c->mem);
	return 0;
}

static ssize_t char_mem_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	struct CharMemoryDev *c = file->private_data;
	char *mem = c->mem;
	int size = c->size;
	if (*ppos + count > size) {
		count = size - *ppos;
	}
	if (copy_to_user(buf, mem + *ppos, count)) {
		printk("copy_to_user error\n");
		return -EFAULT;
	}
	*ppos += count;
	return count;
}

static ssize_t char_mem_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	struct CharMemoryDev *c = file->private_data;
	char *mem = c->mem;
	int size = c->size;
	if (*ppos + count > size) {
		printk("write range out of memory\n");
		return -ENOMEM;
	}
	if (copy_from_user(mem + *ppos, buf, count)) {
		printk("copy_from_user error\n");
		return -EFAULT;
	}
	*ppos += count;		
	return count;
}

static loff_t char_mem_llseek(struct file *file, loff_t offset, int whence)
{
	return default_llseek(file, offset, whence);
}

static long char_mem_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct CharMemoryDev *c = file->private_data;
	char *mem = c->mem;
	int size = c->size;
	switch (cmd) {
		case CLEAR_ZERO:
			memset(mem, 0, size * sizeof(char));
			break;
	}
	return 0;
}

static struct file_operations fops = {
	.read = char_mem_read,
	.write = char_mem_write,
	.llseek = char_mem_llseek,
	.open = char_mem_open,
	.release = char_mem_release,
	.unlocked_ioctl = char_mem_ioctl,
};

static int __init char_mem_dev_init(void)
{
	int ret;
	struct class *class = NULL;
	struct device *cdevice = NULL;
	printk("char mem dev module init\n");
	printk("[module number][%d]\n", num);
	printk("[module author][%s]\n", name);

	chrdev = (struct CharMemoryDev*)kzalloc(sizeof(struct CharMemoryDev), GFP_KERNEL);
// 注册设备，这个函数封装了从register_chrdev_region(alloc_chrdev_region)--->cdev_init(cdev_alloc)和cdev_add的一系列
// 字符设备注册函数
	ret = register_chrdev(0, DEVICE_NAME, &fops);
	if (ret < 0) {
		printk("register_chrdev fail, error=%d\n", ret);
		goto out;
	}
	chrdev->major = ret;
// 创建类，为之后自动创建设备文件做铺垫
	class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(class)) {
		ret = ERR_PTR(class);
		printk("class_create failed!Error code=%d\n", ret);
		goto fail_class_create;
	}
	chrdev->class = class;
// 自动创建设备文件，需要1.class类，2.父类，3.注册的设备号，4.设备的私有数据，5.设备名词
// 可以创建多个设备文件，由于register_char注册了256个次设备，因此这里可以最多创建256个设备文件
	cdevice = device_create(class, NULL, MKDEV(chrdev->major, 0), NULL, DEVICE_NAME);
	if (IS_ERR(cdevice)) {
		ret = ERR_PTR(cdevice);
		printk("device_create failed!Error code=%d\n", ret);
		cdevice = NULL;
		goto fail_device_create;
	}
	chrdev->device = cdevice;
	return 0;
fail_device_create:
	class_destroy(chrdev->class);
fail_class_create:
	unregister_chrdev(chrdev->major, DEVICE_NAME);
out:
	kfree(chrdev);
	return ret;
}

static void __exit char_mem_dev_exit(void)
{
// 删除device文件的时候，第二参数设备号一定要和创建设备的设备号相同，不然销毁设备文件失败
	device_destroy(chrdev->class, MKDEV(chrdev->major, 0));
	class_destroy(chrdev->class);
	unregister_chrdev(chrdev->major, DEVICE_NAME);
	kfree(chrdev);
	printk("char mem dev module exit\n");
}

module_init(char_mem_dev_init);
module_exit(char_mem_dev_exit);

// 内核模块可以在insmod(modprobe)的时候传入参数
 /**
 * module_param - typesafe helper for a module/cmdline parameter
 * @name: the variable to alter, and exposed parameter name.
 * @type: the type of the parameter
 * @perm: visibility in sysfs.
 *
 * @name becomes the module parameter, or (prefixed by KBUILD_MODNAME and a
 * ".") the kernel commandline parameter.  Note that - is changed to _, so
 * the user can use "foo-bar=1" even for variable "foo_bar".
 *
 * @perm is 0 if the variable is not to appear in sysfs, or 0444
 * for world-readable, 0644 for root-writable, etc.  Note that if it
 * is writable, you may need to use kernel_param_lock() around
 * accesses (esp. charp, which can be kfreed when it changes).
 *
 * The @type is simply pasted to refer to a param_ops_##type and a
 * param_check_##type: for convenience many standard types are provided but
 * you can create your own by defining those variables.
 *
 * Standard types are:
 *  byte, hexint, short, ushort, int, uint, long, ulong
 *  charp: a character pointer
 *  bool: a bool, values 0/1, y/n, Y/N.
 *  invbool: the above, only sense-reversed (N = true).
 *
 * #define module_param(name, type, perm)  
 */
module_param(name, charp, S_IRUGO);
module_param(num, int, S_IRUGO);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Guo's char dev module exercise");

