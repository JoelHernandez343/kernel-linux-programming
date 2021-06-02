/*
 * Joel Harim Hernández Javier @ 2021
 * Code under MIT license
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/moduleparam.h>

#include <asm/io.h>

/* constants */
#define ADDR_BASE_GPIO 0x3f200000

/* module information */
MODULE_LICENSE("MIT");
MODULE_AUTHOR("JOEL HARIM HERNÁNDEZ JAVIER");
MODULE_DESCRIPTION("Practice 3");
MODULE_VERSION("1.0.0");

/* parameters */
static int option = 0;
module_param(option, int, 0660);
MODULE_PARM_DESC(option, "0: Iddle. 1: Draw school id until finish");

static char *school_id = "0000000000";
module_param(school_id, charp, 0660);
MODULE_PARM_DESC(school_id, "School id");

/* global variables */
struct task_struct *kthread;

volatile uint32_t *virtual_gpio;

char digits[][8] = {
    "1111110",
    "0110000",
    "1101101",
    "1111001",
    "0110011",
    "1011011",
    "1011111",
    "1110000",
    "1111111",
    "1110011",
    "0000001"
};

int segments[] = {17, 18, 27, 22, 23, 24, 10};

/* function definitions */

void show_char(int chr);
void show_id(const char *id);
void show_iddle(void);

void config_gpio(int gpio_number, int mode);
void config_all_gpio(void);
void set_value(int gpio_number, int value);

/* function implementations */

static int thread_fn(void *args){
    int id = *(int *)args;

    printk(KERN_INFO"Thread worker has been started.\n");

    while (!kthread_should_stop()){
        schedule();

        switch (option) {
            case 0:
                show_iddle();
                break;
        
            case 1:
                show_id(school_id);
                break;
        }

        option = 0;
    }

    return id;
}


/* Init and exit funcions */
static int __init init_fn(void){
    static int thread_id = 1;

    printk(KERN_INFO"Initializing practice 3 :)\n");

    /* gpio configuration */
    virtual_gpio = (uint32_t *)ioremap(ADDR_BASE_GPIO, 0x30);

    if (virtual_gpio == NULL){
        printk(KERN_ERR"Error getting virtual dir, leaving.\n");
        return -1;
    }

    config_all_gpio();

    /* thread initilization */
    kthread = kthread_create(thread_fn, (void *)&thread_id, "kpractice3_thread");

    if (IS_ERR(kthread)){
        printk(KERN_ERR"Error creating thread, leaving.\n");

        return PTR_ERR(kthread);
    }

    wake_up_process(kthread);
    printk(KERN_INFO"Thread created with pid: %d and name: %s.\n", kthread->pid, kthread->comm);

    return 0;
}

static void __exit exit_fn(void){
    int thread_ret;

    printk(KERN_INFO"Finishing execution...\n");

    /* thread termination */
    thread_ret = kthread_stop(kthread);

    if (thread_ret == -EINTR){
        printk(KERN_ERR"Error finishing thread :(\n");
        return;
    }

    printk(KERN_ERR"Thread finished with value %d\n", thread_ret);

}

/* show functions */
void show_char(int chr){
    char *digit = digits[chr];
    register int i;
    
    for (i = 0; digit[i] != 0; ++i){
        set_value(segments[i], digit[i] - '0');
    }
}

void show_id(const char *id){
    register int i;

    for (i = 0; i < 10; ++i){
        printk(KERN_INFO"%c\n", id[i]);
        show_char(id[i] - '0');
        ssleep(1);
    }
}

void show_iddle(void){
    show_char(10);
}

/* gpio functions */
void config_gpio(int gpio, int mode){
    int gpfsel = gpio / 10;
    int bit = mode == 0 ? 1 : 0;
    int bitRange = (gpio % 10);
        bitRange += (bitRange << 1);

    virtual_gpio[gpfsel] = (virtual_gpio[gpfsel] & ~(7 << bitRange)) | (bit << bitRange);
}

void config_all_gpio(void){
    register int i;

    for (i = 0; i < 7; ++i){
        config_gpio(segments[i], 0);
    }
}

void set_value(int gpio, int value){
    int bit = gpio >> 5;
    int offset = bit + (value == 1 ? 7 : 10);
    int bitRange = gpio % 32;

    virtual_gpio[offset] = 1 << bitRange;
}

module_init(init_fn);
module_exit(exit_fn);

