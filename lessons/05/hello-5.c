#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Hernández");
MODULE_DESCRIPTION("Simple kernel module. Demostración de parámetros.");
MODULE_VERSION("4.0.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");

// static int myvar __initdata = 10;
static int irq = 10;

module_param(irq, int, 0660);
MODULE_PARM_DESC(irq, "Número de interrupción. Entero.");

static int __init init_fun(void){
    printk(KERN_INFO"Initializing example 1 of parameters for kernel modules.\n");
    printk(KERN_INFO"IRQ in init_fun is %d.\n", irq);
    return 0;
}

static void __exit exit_fun(void){
    printk(KERN_INFO"Finising the execution of the example 1.\n");
    printk(KERN_INFO"IRQ in init_fun is %d.\n", irq);
}

module_init(init_fun);
module_exit(exit_fun);