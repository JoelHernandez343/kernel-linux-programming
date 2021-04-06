/*
 *  thread-4.c - Demostracion de la ejecución de un hilo en espacio de kernel
 *  se usa la función kthread_create() y wake_up_process(). Se vinvula el hilo
 *  a un procesador con la funcion kthread_bind()
 */
#include <linux/module.h>	/* Necesaria para todos los modulos 		*/
#include <linux/kernel.h>	/* Necesaria para KERN_INFO 			*/
#include <linux/init.h>		/* Necesaria para las macros de documentacion	*/
#include <linux/moduleparam.h>	/* Necesaria para las macros de parametros 	*/
#include <linux/kthread.h>	/* Necesaria para los hilos 			*/
#include <linux/delay.h>	/* Necesaria para las funciones de tiempo	*/
#define MAX 16
#define THREADS 4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VICTOR HUGO GARCIA ORTEGA");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_VERSION("4.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");

static int A[MAX] = {12, 45, 87, 38, 97, -45, 44, 88, 22, 43, -5, -23, -34, -8, 17, 20};
static int B[MAX] = {66, 3, 48, 23, 21, 9, 4, 8, 2, -4, -8, -20, -10, -56, 88, 54};
static int C[MAX];

struct task_struct *kthreads[THREADS];

static int thread_fun( void *arg )
{
	int id = *(int *)arg;
	int start = id * MAX / THREADS;
	int end = start + MAX / THREADS;
	int cpu;
	
	register int i = start;

	printk(KERN_INFO "Iniciando la ejecucion de la funcion hilo_kernel\n");

	while( !kthread_should_stop() )
	{
		schedule();
		for (; i < end; ++i){
			C[i] = A[i] * B[i];
		}

		cpu = smp_processor_id();
		printk(KERN_INFO"Ejecución en CPU: %d\n", cpu);
	}

	return id;
}

static int __init funcion_inicio(void)
{
	
	register int i;
	static int ids_thread[THREADS];
	printk(KERN_INFO "Iniciando el ejemplo 5 de HPC usando hilos de kernel\n");

	for (i = 0; i < THREADS; ++i){
		ids_thread[i] = i;
		kthreads[i] = kthread_create(thread_fun, (void *)&ids_thread[i], "kmy_thread");

		if( IS_ERR(kthreads[i]) ){
			printk(KERN_ERR "Error al crear el hilo de kernel\n");

			return PTR_ERR(kthreads[i]);
		}

		wake_up_process( kthreads[i] );
		printk(KERN_INFO "Hilo creado con pid: %d y nombre: %s\n", kthreads[i]->pid, kthreads[i]->comm);
	}


	/*
	 * Un valor de retorno diferente de 0 significa que
	 * init_module fallo; el modulo no se puede cargar
	 */
	return 0;
}

static void __exit funcion_exit(void)
{
	int ret_threadk;
	register int i;
	printk(KERN_INFO "Terminando la ejecucion\n");

	for (i = 0; i < THREADS; ++i){
		ret_threadk = kthread_stop( kthreads[i] );
		
		if( ret_threadk == -EINTR )
			printk(KERN_ERR "Error en la terminacion del hilo\n");
		else
			printk(KERN_INFO "Terminacion del hilo con valor: %d \n", ret_threadk);

	}

	for (i = 0; i < MAX; ++i){
		printk(KERN_INFO"C[%d]: %d \n", i, C[i]);
	}
}

module_init( funcion_inicio );
module_exit( funcion_exit );
