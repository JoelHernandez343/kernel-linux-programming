/*
 * Device driver with dinamic major and minor number
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Hernández");
MODULE_DESCRIPTION("Simple kernel module.");
MODULE_VERSION("4.0.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");


dev_t device;


static int __init init_fun(void){
    int ret;
    
    printk(KERN_INFO"Initializing DDC\n");
    printk(KERN_INFO"Registering character device driver\n");

    ret = alloc_chrdev_region(&device, 0, 1, "ESCOM_DDC");
    if (ret < 0){
        printk(KERN_ERR"Error registering character device driver\n");
        return ret;
    }

    printk(KERN_INFO"Registering sucesfully %d, %d\n", MAJOR(device), MINOR(device));
    
    return 0;
}

static void __exit exit_fun(void){
    printk(KERN_INFO"Finishing the execution of kernel module.\n");
    unregister_chrdev_region(device, 1);
}

module_init(init_fun);
module_exit(exit_fun);