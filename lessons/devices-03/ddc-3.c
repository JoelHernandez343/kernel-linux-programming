/*
 *  ddc 3 Asignacion de num mayor y menor, creacion de clase y archivo de dispositivo en un ddc
	con asignación dinámica y automática
 */
#include <linux/module.h>			/* Necesaria para todos los modulos 	*/
#include <linux/kernel.h>			/* Necesaria para KERN_INFO 			*/
#include <linux/init.h>				/* Necesaria para las macros 			*/
#include <linux/kdev_t.h> 			//PA  MINOR y MAJOR
#include <linux/fs.h>
#include <linux/device.h>


MODULE_LICENSE("GPL");							/* Tipo de licencia								*/
MODULE_AUTHOR("io");				/* Autor del módulo 							*/
MODULE_DESCRIPTION("Manejo de macro __init");	/* Descripción de la funcionalidad del módulo 	*/
MODULE_VERSION("1.0");							/* Versión del módulo 							*/
MODULE_INFO(driver, "PULSO CARDIACO"); 			/* Información personalizada del usuario		*/

dev_t dispositivo;
static struct class *dev_class;
static struct device *dev_file;

static int __init funcion_inicio(void){
	int ret;

	printk(KERN_INFO "Registrando el device driver de caracter (DDC) \n");
	ret= alloc_chrdev_region(&dispositivo,0,1,"ESCOM_DDC");

	if(ret <0){
		printk(KERN_ERR "Error al registrar el device driver de caracter \n");
		return ret;
	}

	printk(KERN_INFO "Dispositivo registrado exitosamente \n");
	printk(KERN_INFO "Numero mayor asignado: %d \n",MAJOR(dispositivo));
	printk(KERN_INFO "Numero mayor asignado: %d \n",MINOR(dispositivo));

	dev_class= class_create(THIS_MODULE,"ESCOM_class");

	if(IS_ERR(dev_class)){
		printk(KERN_ERR "Error al crear la clase del dispositivo \n");
		unregister_chrdev_region(dispositivo,1);

		return PTR_ERR(dev_class);
	}
	printk(KERN_INFO "Clase creada exitosamente \n");
	

	dev_file= device_create(dev_class,NULL,dispositivo,NULL,"ESCOM_DEVICE");

	if(IS_ERR(dev_file)){
		printk(KERN_ERR "Error al crear la clase del dispositivo \n");
		class_destroy(dev_class);
		unregister_chrdev_region(dispositivo,1);

		return PTR_ERR(dev_file);
	}
	printk(KERN_INFO "Dispositivo creado exitosamente \n");


	return 0;
}

static void __exit funcion_exit(void){
	printk(KERN_INFO "Terminando el device driver de caracter\n");

	device_destroy(dev_class,dispositivo);
	class_destroy(dev_class);
	unregister_chrdev_region(dispositivo,1);

}

module_init(funcion_inicio);
module_exit(funcion_exit);
