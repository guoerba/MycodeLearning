// 最基本的两个头文件
#include <linux/module.h>
#include <linux/init.h>

// 入参（默认值）
static char *name = "Guo";
static int num = 1000;

static int __init char_mem_dev_init(void)
{
	printk("char mem dev module init\n");
	printk("[module author][%s]\n", name);
	printk("[module number][%d]\n", num);
	return 0;
}

static void __exit char_mem_dev_exit(void)
{
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

