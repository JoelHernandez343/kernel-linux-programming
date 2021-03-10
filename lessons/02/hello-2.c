#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init init_fun(void){
    printk(KERN_INFO"Hello world!, initializing the module 2.\n");
    return 0;
}

static void __exit exit_fun(void){
    printk(KERN_INFO"Finising the execution of the module 2.\n");
}

module_init(init_fun);
module_exit(exit_fun);