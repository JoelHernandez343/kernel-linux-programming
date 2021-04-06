#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Hernández");
MODULE_DESCRIPTION("Simple kernel module.");
MODULE_VERSION("4.0.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");

static int myvar __initdata = 10;

static int __init init_fun(void){
    printk(KERN_INFO"Hello world!, initializing the module 4.\n");
    printk(KERN_INFO"My variable is %d.\n", myvar);
    return 0;
}

static void __exit exit_fun(void){
    printk(KERN_INFO"Finising the execution of the module 4.\n");
}

module_init(init_fun);
module_exit(exit_fun);