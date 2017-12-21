#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/moduleparam.h>
#include<linux/list.h>

static int pid;
module_param(pid,int,0644);

static int hello_init(void){
	struct task_struct *p, *parent, *son;
	for_each_process(p) if((p->pid) == pid) break;
	if(p == (&init_task)) printk(KERN_ALERT"ERROR!\n");

	printk(KERN_ALERT"***** pid = %d *****", pid);
	
	parent = p->parent;
	printk(KERN_ALERT"*** parent: %s  pid=%d", parent->comm, parent->pid);
	
	struct list_head *pos;
	printk(KERN_ALERT"*** son: \n");
	list_for_each(pos, &(p->children)){
		son = list_entry(pos, struct task_struct, sibling);
		printk(KERN_ALERT"    %-15s  pid=%d", son->comm, son->pid);
	}
	return 0;
}
static void hello_exit(void){
	printk(KERN_ALERT"goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
