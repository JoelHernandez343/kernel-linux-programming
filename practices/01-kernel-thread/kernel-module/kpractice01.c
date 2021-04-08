/*
 * Joel Harim Hernández Javier @ 2021
 * This code is under MIT license.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/err.h>

#define MAX 8

/* Module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JOEL HARIM HERNÁNDEZ JAVIER");
MODULE_DESCRIPTION("Practice with kernel module n threads.");
MODULE_VERSION("1.0.0");

/* Parameters */
static int option = 0;
module_param(option, int, 0660);
MODULE_PARM_DESC(option, "[1: Average, 2: Sorting, 3: Even numbers]");

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


/* Thread functions */

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

void showArray(const int *array, const char *name){
    register int i;
    for (i = 0; i < length; ++i){
        printk(KERN_INFO"%s[%d]: %d.\n", name, i, array[i]);
    }
}

struct task_struct *kthread;

static int thread_fn(void *args){
    int id = *(int *)args;

    printk(KERN_INFO"Thread worker has been started.\n");

    while (!kthread_should_stop()){
        schedule();

        switch (option) {
            case 1:
                printk(KERN_INFO"Method invoked. Calculating average.\n");
                calc_average();
                printk(KERN_INFO"Average: %d.\n", average);
                break;
        
            case 2:
                printk(KERN_INFO"Method invoked. Sorting data.\n");
                sort();
                showArray(data, "data");
                break;

            case 3:
                printk(KERN_INFO"Method invoked. Finding even numbers.\n");
                find_even_numbers();
                showArray(even_data, "even_data");
                break;
        }

        option = 0;
    }

    return id;
}

/* Init and exit funcions */
static int __init init_fn(void){
    static int thread_id = 1;

    printk(KERN_INFO"Initializing practice 1 :)\n");

    kthread = kthread_create(thread_fn, (void *)&thread_id, "kpractice1_thread");

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

    thread_ret = kthread_stop(kthread);

    if (thread_ret == -EINTR){
        printk(KERN_ERR"Error finishing thread :(\n");
        return;
    }

    printk(KERN_ERR"Thread finished with value %d\n", thread_ret);
}

module_init(init_fn);
module_exit(exit_fn);