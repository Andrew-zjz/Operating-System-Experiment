#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/sem.h>  
#include <errno.h>

/***
*about shm    
*/
#define TEXT_SZ 2048  
#define SHMKEY 1111

struct shared_use_st {  
    char text[TEXT_SZ];//记录写入和读取的文本  
};  
    

/***
*about sem
*/
#define SEMKEY 15038888
#define SENDERID 0
#define RECIEVERID 1
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};


static int comm_create_sem(int flags,int num){
  int sem_id;
  if((sem_id=semget(SEMKEY,num,flags|0666))<0)
    printf("semget errno,%d:%s\n",errno,strerror(errno));
  return sem_id;
}

int create_sem(int num){
  int flags=IPC_CREAT | IPC_EXCL;
  int sem_id=comm_create_sem(flags,num);
  union semun v;
  
  //init
  v.val=0; 
  if(semctl(sem_id,SENDERID,SETVAL,v)<0){ // sender
    printf("init error,%d:%s\n",errno,strerror(errno));
  }

  v.val=0;
  if(semctl(sem_id,RECIEVERID,SETVAL,v)<0){ // reciever
    printf("init error,%d:%s\n",errno,strerror(errno));
  }
  return sem_id;
}

int get_sem()
{
  int flags=0;
  return comm_create_sem(flags,0);
}


void P_sem(int sem_id,int index)
{
  struct sembuf s;
  s.sem_num=index;
  s.sem_op=-1;
  s.sem_flg=0;
  if(semop(sem_id,&s,1)<0)
  {
    printf("op errro");
  }
}

void V_sem(int sem_id,int index)
{
  struct sembuf s;
  s.sem_num=index;
  s.sem_op=1;
  s.sem_flg=0;
  if(semop(sem_id,&s,1)<0)
  {
    printf("op error");
  }

}

void destory_sem(int sem_id)
{
  semctl(sem_id,SENDERID,IPC_RMID);
  semctl(sem_id,RECIEVERID,IPC_RMID);
}

