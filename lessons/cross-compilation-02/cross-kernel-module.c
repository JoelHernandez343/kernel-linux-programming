#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init init_fun(void){
    printk(KERN_INFO"Hello arm from x86!, initializing kernel module.\n");
    return 0;
}

static void __exit exit_fun(void){
    printk(KERN_INFO"Finishing the execution, good bye arm!.\n");
}

module_init(init_fun);
module_exit(exit_fun);