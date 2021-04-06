/*
 *  param-3.c - Demostracion de parametros en el modulo de kernel
 *  se usa un parametro entero (int), una cadena (charp) y un arreglo(int)
 */
#include <linux/module.h>	/* Necesaria para todos los modulos 		*/
#include <linux/kernel.h>	/* Necesaria para KERN_INFO 			*/
#include <linux/init.h>		/* Necesaria para las macros de documentacion	*/
#include <linux/moduleparam.h>	/* Necesaria para las macros de parametros 	*/
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/err.h>

#define MAX 5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VICTOR HUGO GARCIA ORTEGA");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_VERSION("4.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");


struct task_struct *kthread;

static int thread_fn(void *args){
	int id = *(int *)args;
	int counter = 0;

	printk(KERN_INFO"Thread running!\n");

	while(!kthread_should_stop()){
		ssleep(5);
		printk(KERN_INFO"Scheduler: %d\n", counter++);
	}

	return id;
}


static int __init funcion_inicio(void)
{
	static int thread_id = 10;

	kthread = kthread_create(thread_fn, (void *)&thread_id, "kmy_thread");

	if (IS_ERR(kthread)){
		printk(KERN_ERR"Error creating thread.");
		return PTR_ERR(kthread);
	}

	wake_up_process(kthread);
	printk(KERN_INFO"Thread created w/ pid %d and name %s\n", kthread->pid, kthread->comm);

	return 0;
}

static void __exit funcion_exit(void)
{
	int thread_ret = kthread_stop(kthread);

	printk(KERN_INFO "Finishing example 1 of kernel threads\n");

	if (thread_ret == -EINTR){
		printk(KERN_ERR"The thread has stopped with errors.\n");
	}
	else {
		printk(KERN_INFO"The thread has stopped without errors with value %d.\n", thread_ret);
	}
}

module_init( funcion_inicio );
module_exit( funcion_exit );
