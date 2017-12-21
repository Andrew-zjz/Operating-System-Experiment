#include "head.h"
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <sys/shm.h>  // share memory http://blog.csdn.net/ljianhui/article/details/10253345
#include <sys/sem.h> // semaphore http://blog.csdn.net/ljianhui/article/details/10243617
int main(){  
    void *shm = NULL; //分配的共享内存的首地址  
    struct shared_use_st *shared; //point the same addr to shm   
    int shmid; //共享内存标识符
    int semid; //semaphore id

    //创建共享内存  
    shmid = shmget(SHMKEY, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1){  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  

    //get semaphore
    semid = get_sem();  // 2 sem !! 0-sender 1-reciever

    //将共享内存连接到当前进程的地址空间  
    shm = shmat(shmid, 0, 0);  
    if(shm == (void*)-1){  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  

    //设置共享内存  
    shared = (struct shared_use_st*)shm;  

    //读取共享内存中的数据    
    // while(1){ 
    printf("***reciever***: I'm waiting!\n");   
    P_sem(semid, RECIEVERID);
    printf("***reciever***: recieve %s",shared->text);

    printf("\n***reciever***: I'm sending \"over\"!\n");
    int i;
    for(i = 0; i < 5; ++i) {
		int j;
		for(j = 0; j < i; ++j) printf(".");
		printf("\n");
		sleep(1);
	}   

    strcpy(shared->text, "over\n");
    V_sem(semid, SENDERID); 
    // }  
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1){  
        printf("shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  

    //删除共享内存  
    sleep(2);
    if(shmctl(shmid, IPC_RMID, 0) == -1){  
        printf("shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  
    destory_sem(semid);
    printf("***reciever***: remove shm && sem success!\n");
    exit(EXIT_SUCCESS);  
}  