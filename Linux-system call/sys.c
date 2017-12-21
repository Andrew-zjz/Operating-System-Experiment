SYSCALL_DEFINE5(exp1, pid_t, pid, int,flag, int,nicevalue, void __user*,prio, void __user*,nice){
        struct task_struct *p;
	int nc,pr;

	for_each_process(p) if(p->pid == pid) break;
	if(p==(&init_task)) return EFAULT;

	if(flag==1) set_user_nice(p,nicevalue);
	else if(flag != 0) return EFAULT;

	nc=task_nice(p);
	pr=p->prio;
	copy_to_user(nice,(void __user*)(&nc), sizeof(int));
	copy_to_user(prio,(void __user*)(&pr), sizeof(int));
	
	return 0;
}