/*
 * Joel Harim Hernández Javier @ 2021
 * Code under MIT license
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/err.h>

#include <asm/io.h>

/* function definitions */

void cb_fn(void);

void show_char(int chr);
void show_id(const char *id);
void show_iddle(void);

void config_gpio(int gpio_number, int mode);
void config_all_gpio(void);
void set_value(int gpio_number, int value);

/* module information */
MODULE_LICENSE("MIT");
MODULE_AUTHOR("JOEL HARIM HERNÁNDEZ JAVIER");
MODULE_DESCRIPTION("Practice 3");
MODULE_VERSION("1.0.0");

/* parameters */

static char *school_id = "0000000000";
module_param(school_id, charp, 0660);
MODULE_PARM_DESC(school_id, "School id");

/* option parameter */

static int option = 0;

int set_param(const char *value, const struct kernel_param *kp){
    int ret;

    if (option == 1){
        printk(KERN_ERR"Already showing another school id, leaving.\n");
        return 0;
    }

    ret = param_set_int(value, kp);

    if (ret != 0){
        printk(KERN_ERR"Error setting option parameter, leaving.\n");
        return ret;
    }

    cb_fn();

    return ret;
}

int get_param(char *buffer, const struct kernel_param *kp){
    int ret;
    ret = param_get_int(buffer, kp);
    
    if (ret > 0){
        printk(KERN_INFO "Parametro de salida: %s\n", buffer);
        return ret;
    }

    return -EPERM;
}

static const struct kernel_param_ops option_accessors = {
    .set = set_param,
    .get = get_param
};

module_param_cb(option, &option_accessors, &option, 0660);
MODULE_PARM_DESC(option, "0: Iddle. 1: Draw school id until finish");


/* global variables */

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

/* function implementations */

void cb_fn(void){
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


/* Init and exit funcions */
static int __init init_fn(void){
    printk(KERN_INFO"Initializing practice 5 :)\n");

    /* gpio configuration */
    virtual_gpio = (uint32_t *)ioremap(0x3f200000, 0x30);

    if (virtual_gpio == NULL){
        printk(KERN_ERR"Error getting virtual dir, leaving.\n");
        return -1;
    }

    config_all_gpio();

    return 0;
}

static void __exit exit_fn(void){
    printk(KERN_INFO"Finishing execution...\n");
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
        udelay(1);
    }
}

void show_iddle(void){
    show_char(10);
}

/* gpio functions */
void config_gpio(int gpio_number, int mode){
    int gpfsel = gpio_number / 10;
    int bitRange = (gpio_number % 10);
        bitRange += (bitRange << 1);

    virtual_gpio[gpfsel] = (virtual_gpio[gpfsel] & ~(7 << bitRange)) | (mode << bitRange);
}

void config_all_gpio(void){
    register int i;

    for (i = 0; i < 7; ++i){
        config_gpio(segments[i], 0);
    }
}

void set_value(int gpio_number, int value){
    int bit = gpio_number >> 5;
    int offset = bit + (value == 1 ? 7 : 10);

    int bitRange = gpio_number % 32;

    virtual_gpio[offset] |= 1 << bitRange;
}

module_init(init_fn);
module_exit(exit_fn);

