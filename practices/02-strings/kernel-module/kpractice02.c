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
MODULE_PARM_DESC(option, "[1: Count coincidences, 2: Calculating length]");

static char *str = "esta es la optativa de advanced computing systems programming";
module_param(str, charp, 0660);
MODULE_PARM_DESC(str, "Input string.");

static char *letter = "";
module_param(letter, charp, 0660);
MODULE_PARM_DESC(letter, "Letter to search. Only fisrt character will be processed.");

static int coincidences;
module_param(coincidences, int, 0440);
MODULE_PARM_DESC(coincidences, "Number of coincidences.");

static int length;
module_param(length, int, 0440);
MODULE_PARM_DESC(length, "String length.");


/* Thread functions */
void count_coincidences(void){
    register int i, result = 0;

    for (i = 0; str[i]; ++i){
        result += str[i] == letter[0];
    }

    coincidences = result;
}

void len(void) {
    register int result = 0;

    for (result = 0; str[result]; ++result);

    length = result;
}

struct task_struct *kthread;

static int thread_fn(void *args){
    int id = *(int *)args;

    printk(KERN_INFO"Thread worker has been started.\n");

    while (!kthread_should_stop()){
        schedule();

        switch (option) {
            case 1:
                printk(KERN_INFO"Method invoked. Counting coincidences.\n");
                count_coincidences();
                printk(KERN_INFO"Coincidences: %d.\n", coincidences);
                break;
        
            case 2:
                printk(KERN_INFO"Method invoked. Calculating length.\n");
                len();
                printk(KERN_INFO"Length: %d.\n", length);
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