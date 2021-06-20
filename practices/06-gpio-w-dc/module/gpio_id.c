/*
 * Joel Harim Hernández Javier @ 2021
 * Code under MIT license
 */

#include <linux/fs.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/device.h>

#include <asm/io.h>

/* constants */
#define ADDR_BASE_GPIO 0x3f200000
#define MEM_SIZE 1024

/* function definitions */
void cb_fn(void);

void show_char(int chr);
void show_id(const char *id);
void show_iddle(void);

void config_gpio(int gpio_number, int mode);
void config_all_gpio(void);
void set_value(int gpio_number, int value);

/* module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JOEL HARIM HERNÁNDEZ JAVIER");
MODULE_DESCRIPTION("Practice 6");
MODULE_VERSION("1.0.0");

/* global variables */
static dev_t device;
static struct class *dev_class;
static struct device *dev_file;
static struct cdev dev_cdev;
static char *buffer;

static char *school_id = "0000000000";
static int status;

/* driver configuration definitions */

static int driver_open (struct inode *inode, struct file *file);
static int driver_release (struct inode *inode, struct file *file);
static ssize_t driver_read (struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t driver_write (struct file *filp, const char *buf, size_t len, loff_t *off);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = driver_read,
    .write = driver_write,
    .open = driver_open,
    .release = driver_release
};

/* global variables 2 */

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
    switch (status) {
        case 0:
            show_iddle();
            break;
    
        case 1:
            show_id(school_id);
            break;
    }

    status = 0;
    show_iddle();
}


/* show functions */
void show_char(int chr){
    char *digit;
    register int i;

    if (chr < 0 || chr > 10){
        show_iddle();
        return;
    }

    digit = digits[chr];

    printk(KERN_INFO"%c\n", chr + '0');
    
    for (i = 0; digit[i] != 0; ++i){
        set_value(segments[i], digit[i] - '0');
    }
}

void show_id(const char *id){
    register int i;

    for (i = 0; i < 10; ++i){
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

/* driver config implementation */

static int driver_open (struct inode *inode, struct file *file){
    printk(KERN_INFO"Executing the open operation \n");

    buffer = (char *)kmalloc(MEM_SIZE, GFP_KERNEL);
    if (buffer == NULL){
        printk(KERN_ERR "Error allocating memory bro :(\n");
        return -ENOMEM;
    }

    return 0;
}

static int driver_release (struct inode *inode, struct file *file){
    printk(KERN_INFO "Executing release operation\n");
    kfree(buffer);

    return 0;
}

static ssize_t driver_read (struct file *filp, char __user *buf, size_t len, loff_t *off){
    int length, ret;

    printk(KERN_INFO "Executing read operation\n");
    printk(KERN_INFO "Length: %d, offset: %lld \n", len, *off);

    if (*off == 0 && len > 0){
        strcpy(buffer, school_id);
        length = strlen(buffer) + 1;
        ret = copy_to_user(buf, buffer, length);

        if (ret){
            printk(KERN_ERR "Error copying to user space buffer\n");
            return -EFAULT;
        }

        *off += length;
        return length;
    }

    return 0;
}

static ssize_t driver_write (struct file *filp, const char *buf, size_t len, loff_t *off){
    int ret, bytes_to_copy;

    printk(KERN_INFO "Executing write operation\n");
    printk(KERN_INFO "Length: %d, offset: %lld\n", len, *off);

    ret = copy_from_user(buffer, buf, len);

    if (ret){
        printk(KERN_ERR "Error copying from user space buffer\n");
        return -EFAULT;
    }

    printk(KERN_INFO "Buffer received: %s\n", buffer);

    if (status == 1){
        printk(KERN_INFO "Already showing school id\n");
        return len;
    }


    // Copy the received buffer to school_id
    memset(school_id, '0', 10);
    bytes_to_copy = len > 10 ? 10 : len;
    
    memcpy(school_id, buffer, bytes_to_copy);
    school_id[10] = 0;

    cb_fn();

    return len;
}

/* Init and exit funcions */
static int __init init_fn(void){
    int ret;

    printk(KERN_INFO"Initializing practice 6 :)\n");

    /* driver configuration */
    ret = alloc_chrdev_region( &device, 0, 1, "school_id" );
    if (ret < 0){
        printk(KERN_ERR "Error registering character device driver \n");
        return ret;
    }

    printk(KERN_INFO "Device registered successfully... \n");
    printk(KERN_INFO "Major number assigned: %d \n", MAJOR(device));
    printk(KERN_INFO "Minor number assigned: %d \n", MINOR(device));

    cdev_init( &dev_cdev, &fops );
    ret = cdev_add( &dev_cdev, device, 1 );
    if (ret < 0){
        printk(KERN_ERR "Error registering operations\n");
        unregister_chrdev_region( device, 1 );

        return ret;
    }
    printk(KERN_INFO "Operations registered successfully... \n");

    dev_class = class_create(THIS_MODULE, "school_class");
    if (IS_ERR(dev_class)){
        printk(KERN_ERR "Error creating device class \n");
        cdev_del(&dev_cdev);
        unregister_chrdev_region(device, 1);

        return PTR_ERR(dev_class);
    }
    printk(KERN_INFO "Class created successfully... \n");

    dev_file = device_create( dev_class, NULL, device, NULL, "ESCOM_device");
    if (IS_ERR(dev_file)){
        printk(KERN_ERR "Error creating device \n");
        class_destroy(dev_class);
        cdev_del(&dev_cdev);
        unregister_chrdev_region(device, 1);

        return PTR_ERR(dev_file);
    }

    printk(KERN_INFO "Device created successfully... \n");

    /* gpio configuration */
    virtual_gpio = (uint32_t *)ioremap(0x3f200000, 0x30);

    if (virtual_gpio == NULL){
        printk(KERN_ERR"Error getting virtual dir, leaving.\n");

        device_destroy(dev_class, device);
        class_destroy(dev_class);
        cdev_del(&dev_cdev);
        unregister_chrdev_region(device, 1);

        return -1;
    }

    config_all_gpio();

    /* show first iddle */
    show_iddle();

    return 0;
}

static void __exit exit_fn(void){
    printk(KERN_INFO"Finishing execution...\n");

    device_destroy(dev_class, device);
    class_destroy(dev_class);
    cdev_del(&dev_cdev);
    unregister_chrdev_region(device, 1);
}

module_init(init_fn);
module_exit(exit_fn);

