#include <stdio.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#define SEND_KEY 2
#define RCV_KEY 3

typedef struct msgbuf 
{
    long mtype;     
    char mtext[100];  
} MSG_BUF;
int main()
{
    int msg_id;
    MSG_BUF mess_send,mess_rec;
    if((msg_id=msgget(2,IPC_CREAT |0644))<0)
        perror("msgget");
 pid_t b;
int flag=1;
    b = fork();
    if(b==0)
    {
        // child is receiving and parent for sending
        while(flag==1) {
            if((msgrcv(msg_id,&mess_rec,sizeof(mess_rec.mtext),RCV_KEY,0))<0)
                perror("msgrcv");
            printf("Message : %s\n",mess_rec.mtext);
	int result=strcmp(mess_rec.mtext,"bye");
    printf("%d",result);
	if(result==10){
	msgctl(msg_id,IPC_RMID,NULL);
	printf("the queue delted");
	flag=0;
    exit(0);
}	
        }
    }
    else
    {
        // Parent is writing
        while(flag==1){
            mess_send.mtype=SEND_KEY;
            printf("Enter the message\n");
            fgets(mess_send.mtext, sizeof mess_send.mtext, stdin);
            if((msgsnd(msg_id,&mess_send,strlen(mess_send.mtext)+1,0))<0)
                perror("msgsnd");

        int result=strcmp(mess_send.mtext,"bye");
        printf("%d",result);
        if(result==10){
        msgctl(msg_id,IPC_RMID,NULL);
        printf("the queue delted");
	flag=0;
    exit(0);
}
        }
    }
    return 0;
}

