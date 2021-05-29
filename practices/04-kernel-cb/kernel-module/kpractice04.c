/*
 * Joel Harim Hernández Javier @ 2021
 * This code is under MIT license.
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/moduleparam.h>

#define MAX 8

/* function definitions */
void cb_fn(void);

/* module information */
MODULE_LICENSE("MIT");
MODULE_AUTHOR("JOEL HARIM HERNÁNDEZ JAVIER");
MODULE_DESCRIPTION("Practice with kernel module n threads.");
MODULE_VERSION("1.0.0");

/* parameters */

static int data[MAX] = {5, 78, -23, 97, 12, -5, 7, 44};
static int length = MAX;
module_param_array(data, int, &length, 0660);
MODULE_PARM_DESC(data, "Array to sort.");

static int even_data[MAX];
module_param_array(even_data, int, &length, 0440);
MODULE_PARM_DESC(even_data, "Result array for even numbers.");

static int average = 0;
module_param(average, int, 0440);
MODULE_PARM_DESC(average, "Average result.");

/* option parameter */

int set_param(const char *value, const struct kernel_param *kp){
    int ret;
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

static int option = 0;
module_param_cb(option, &option_accessors, &option, 0660);
MODULE_PARM_DESC(option, "[1: Average, 2: Sorting, 3: Even numbers]");

/* cb functions */

// Simple bubble sort. O(n^2)
void sort(void){
    register int i, j;
    for (i = 0; i < length; ++i){
        for (j = i + 1; j < length; ++j){
            if (data[i] > data[j]){
                int aux = data[i];
                data[i] = data[j];
                data[j] = aux;
            }
        }
    }
}

// Store the data's even numbers in even_data
void find_even_numbers(void){
    register int i, j;
    i = j = 0;

    for (j = 0; j < length; ++j){
        if ((data[j] & 1) == 0){
            even_data[i++] = data[j];
        }
    }

    for (; i < length; ++i){
        even_data[i] = 0;
    }
}

// Calculate the data's average and store in average
void calc_average(void){
    register int i;
    int result = 0;

    for (i = 0; i < length; ++i){
        result += data[i];
    }

    average = result / length;
}

void show_array(const int *array, const char *name){
    register int i;
    for (i = 0; i < length; ++i){
        printk(KERN_INFO"%s[%d]: %d.\n", name, i, array[i]);
    }
}


void cb_fn(void){
    switch (option) {
        case 1:
            printk(KERN_INFO"Method invoked. Calculating average.\n");
            calc_average();
            printk(KERN_INFO"Average: %d.\n", average);
            break;
    
        case 2:
            printk(KERN_INFO"Method invoked. Sorting data.\n");
            sort();
            show_array(data, "data");
            break;

        case 3:
            printk(KERN_INFO"Method invoked. Finding even numbers.\n");
            find_even_numbers();
            show_array(even_data, "even_data");
            break;
    }

    option = 0;
}

/* Init and exit funcions */
static int __init init_fn(void){
    printk(KERN_INFO"Initializing practice 4 :)\n");

    return 0;
}

static void __exit exit_fn(void){
    printk(KERN_INFO"Finishing execution...\n");
}

module_init(init_fn);
module_exit(exit_fn);