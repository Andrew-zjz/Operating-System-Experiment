#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

//编译时加-pthread

int main(){
    int filedes[2];//0读管道 1写管道
    pid_t pida,pidb,pidc;
    char buffer[512]={'\0'};
    int readnum;//进程实际读写字节
    sem_t *sem=NULL;//POSIX有名信号量
     
    if((pipe(filedes))<0){
        printf("pipe error!!!\n");
        exit(1);
    }
    
    if((pida=fork())<0){
        printf("fork pida error!!!\n");
        exit(1);
    }
    if(pida==0){
        printf("now is pida(%d)\n",getpid());
        close(filedes[0]);
        sem=sem_open("pv",O_CREAT|O_RDWR,0666,1);
        if(sem==SEM_FAILED){
            printf("sem_open error!!!\n");
            exit(1);
        }
        sem_wait(sem);
        printf("now is pida using pipe\n");
        write(filedes[1],"hello I'm peppa pig.\n",strlen("hello I'm peppa pig.\n"));
        printf("pida using end\n\n");
        sem_post(sem);
        sem_close(sem);
        exit(0);
    }

    if((pidb=fork())<0){
        printf("fork pidb error!!!\n");
        exit(1);
    }
    if(pidb==0){
        printf("now is pidb(%d)\n",getpid());
        close(filedes[0]);
        sem=sem_open("pv",O_CREAT|O_RDWR,0666,1);
        if(sem==SEM_FAILED){
            printf("sem_open error!!!\n");
            exit(1);
        }
        sem_wait(sem);
        printf("now is pidb using pipe\n");
        write(filedes[1],"this is my brother george.\n",strlen("this is my brother george.\n"));
        printf("pidb using end\n\n");
        sem_post(sem);
        sem_close(sem);
        exit(0);
    }

    if((pidc=fork())<0){
        printf("fork pidc error!!!\n");
        exit(1);
    }
    if(pidc==0){
        printf("now is pidc(%d)\n",getpid());
        close(filedes[0]);
        sem=sem_open("pv",O_CREAT|O_RDWR,0666,1);
        if(sem==SEM_FAILED){
            printf("sem_open error!!!\n");
            exit(1);
        }
        sem_wait(sem);
        printf("now is pidc using pipe\n");
        write(filedes[1],"this is mummy pig.\nand this is daddy pig.\n",strlen("this is mummy pig.\nand this is daddy pig.\n"));
        printf("pidc using end\n\n");
        sem_post(sem);
        sem_close(sem);
        exit(0);
    }
    pida = waitpid(pida, NULL, WUNTRACED);
    pidb = waitpid(pidb, NULL, WUNTRACED);
    pidc = waitpid(pidc, NULL, WUNTRACED);
    printf("now pida(%d) pidb(%d) pidc(%d) finished\n",pida,pidb,pidc);
    //printf("wait father 5 seconds\n");
    //sleep(5);
    printf("now is father(%d)\n",getpid());
    close(filedes[1]);
    sem=sem_open("pv",O_CREAT|O_RDWR,0666,1);
    if(sem==SEM_FAILED){
        printf("sem_open error!!!\n");
        exit(1);
    }
    sem_wait(sem);
    printf("now is father using pipe\n");
    readnum=read(filedes[0],buffer,sizeof(buffer));
    printf("father using end\n\n");
    sem_post(sem);
    printf("the number is %d, and they said:\n%s\n",readnum,buffer);
    
    return 0;
}