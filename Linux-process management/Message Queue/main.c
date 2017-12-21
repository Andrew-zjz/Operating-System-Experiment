#include<stdio.h>
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h> 
#include <pthread.h> // thread http://blog.csdn.net/youbang321/article/details/7815707
#include <sys/msg.h>  // message queue http://blog.csdn.net/sty23122555/article/details/51132158
#include <semaphore.h> // semaphore http://blog.csdn.net/tennysonsky/article/details/46496201

#define MSGKEY 1111
#define MAX_TEXT 512
sem_t over;

struct Msg{  
    long int msg_type;  
    char text[MAX_TEXT];  
};  

void *sender(){
	
	struct Msg data;
	data.msg_type = 1;
	
	printf("***sender***:Sender is running!\n");
	int msgid = msgget(MSGKEY, 0666 | IPC_CREAT);  // create or get message queue
	if(msgid < 0){  
        printf("***sender***:msgget failed");  
        exit(0);
    }  

	int end = 0;
	while(1){
		sleep(1);
		printf("Send text: ");
		fgets(data.text, MAX_TEXT, stdin);
		if(!strcmp(data.text, "exit\n")){ // exit
			end = 1;
			strcpy(data.text, "end\n");
		}
		if(msgsnd(msgid, (void*)&data, sizeof(struct Msg), 0) == -1){ // send message          
            printf("***sender***:msgsnd failed\n");  
            exit(0);
        }  
		if(end) break;
	}

	sem_wait(&over); // wait for over
	if(msgrcv(msgid, (void*)&data, sizeof(struct Msg), 0, 0) == -1){  
		printf("***sender***:msgrcv failed\n");  
		exit(0);
	} 
	printf("***sender***: recieve %s",data.text); 
    if(msgctl(msgid, IPC_RMID, 0) == -1){  // delete msg
        printf("***sender***:msgctl(IPC_RMID) failed\n");  
        exit(0);  
    }  
	printf("***sender***: delete msg successfully\n"); 
}

void *reciever(){
	
	struct Msg data;
	data.msg_type = 1;

	printf("***reciever***:Reciever is running!\n");
	int msgid = msgget(MSGKEY, 0666 | IPC_CREAT);  // create or get message queue
	if(msgid < 0){  
        printf("***reciever***:msgget failed with error");  
        exit(0);
    }  
    while(1){  
        if(msgrcv(msgid, (void*)&data, sizeof(struct Msg), 0, 0) == -1){  
            printf("***reciever***:msgrcv failed\n");  
            exit(0);
        }  
        printf("***reciever***: recieve %s",data.text);      
        if(!strcmp(data.text, "end\n")) break; // end
    }  

	printf("\n***reciever***:prepare for send over!!\n");
	int i;
	for(i = 0; i < 5; ++i) {
		int j;
		for(j = 0; j < i; ++j) printf(".");
		printf("\n");
		sleep(1);
	}
	strcpy(data.text, "over\n");
	if(msgsnd(msgid, (void*)&data, sizeof(struct Msg), 0) == -1){ // send "over"          
		printf("***reciever***:msgsnd failed\n");  
		exit(0);
	}  
	printf("***reciever***:send over\n");
	sem_post(&over);
}

int main(){

	pthread_t s, r;

	printf("###Start###\n");
	sem_init(&over, 0, 0);
	
	pthread_create(&s, NULL, sender, NULL); // create sender thread
	pthread_create(&r, NULL, reciever, NULL); // create reciever thread
	pthread_join(r, NULL);
	pthread_join(s, NULL);
	
	sem_destroy(&over);
	return 0;
}

