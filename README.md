# Operating-System-Experiment
Some operating system(OS) experiments based on Linux.

1. Linux-system call
2. Linux-kernel module programming
3. Linux-process management (implement in teams)

There are some details of these experiments below.


## 1. Linux-system call
Add a new system call to the system which can change the nice value of a process.

### Steps to add and call custom system calls
1. **Assign a syscall number**: You can find the *system call table* in `linux-source-xxxx/arch/x86/entry/syscalls/syscall_64.tbl`. You should assign a *syscall number* for own syscall.
2. **Declare the function**:  you should declare the fuction in `linux-source-xxxx/include/linux/syscalls.h` as:
  ```
  asmlinkage long syscall_name(void);
  ```
3. **Implement the syscall**: The code is in `Operating-System-Experiment/Linux-system call/sys.c`, you should put it in `linux-source-xxxx/include/linux/syscalls.h`
4. **Compile the kernel**
5. **Call it**: A example of call method is in `Operating-System-Experiment/Linux-system call/main.c`

## 2. Linux-kernel module programming
There are two modules have been implemented.
**module1**： List the name, pid, state, prio of all the kernel process.(This module don't have any arg.)
**module2**： List a process's parent, siblings, sons, pid, state, prio through PID.(This is module with args.)

### Steps to use the module
1. **Compile**: Just `cd` to the directory. And use the command `make`. After that, you will get a file called `xxxx.ko`.
2. **Insert the module**: 
```
# insmod [filename][module options...]
```
For example: `insmod module1.ko`
3. **Remove the module**: 
```
# rmmod [filename]
```

## 3. Linux-process management
**DIY shell**: This is a shell implement by myself. You can use the command of linux. And you can also use the command implement by myself i.e. cmd1, cmd2, cmd3.<br>
**Communication Pipeline**: Communication between two processes with Pipline.<br>
**Shared Memory**: Communication between two processes with Sharing Memory.<br>
**Message Queue**: Communication between two threads with Message Queue.

And I have used Semaphore in **Shared Memory** and **Message Queue**. **Communication Pipeline** is implement by my teammate.
