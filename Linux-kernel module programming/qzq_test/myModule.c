#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
static int hello_init(void){
	struct task_struct *p;
	for_each_process(p) if(!(p->mm))
		printk(KERN_ALERT"%-15s pid:%-5d state:%-4ld prio:%-5d\n", p->comm, p->pid, p->state, p->prio);
	return 0;
}
static void hello_exit(void){
	printk(KERN_ALERT"goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
