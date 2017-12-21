#include "head.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h> //share memory http://blog.csdn.net/ljianhui/article/details/10253345

int main()
{
	void *shm = NULL;
	struct shared_use_st *shared = NULL;
	char buffer[BUFSIZ + 1];//用于保存输入的文本
	int shmid; //共享内存标识符
    int semid; //semaphore id

	//创建共享内存
	shmid = shmget(SHMKEY, sizeof(struct shared_use_st), 0666|IPC_CREAT);
	if(shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

    //get semaphore
    semid = create_sem(2);  // 2 sem !! 0-sender 1-reciever

	//将共享内存连接到当前进程的地址空间
	shm = shmat(shmid, 0, 0);
	if(shm == (void*)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	//设置共享内存
	shared = (struct shared_use_st*)shm;

	//向共享内存中写数据
	// while(1){ 
	printf("Send text: ");
	fgets(buffer, BUFSIZ, stdin);
	strncpy(shared->text, buffer, TEXT_SZ);

	V_sem(semid, RECIEVERID);
	P_sem(semid, SENDERID);
	printf("***sender***: recieve %s",shared->text);
	// }
	//把共享内存从当前进程中分离
	if(shmdt(shm) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}