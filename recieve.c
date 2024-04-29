#include<signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<unistd.h>
#include <sys/types.h>
#include <string.h>
#define SEND_KEY 3
#define RCV_KEY 2

typedef struct msgbuf {
        long mtype;     
        char mtext[100]; 
}MSG_BUF;
int main()
{
    int msg_id;
int flag=1;
    MSG_BUF mbuf_snd,mbuf_rcv;
    if((msg_id=msgget(2,IPC_CREAT |0644))<0)
        perror("msgget");
    if(fork()==0)
    {
        //child is receiving 
        while(flag==1){
            if((msgrcv(msg_id,&mbuf_rcv,sizeof(mbuf_rcv.mtext),RCV_KEY,0))<0)
                perror("msgrcv");
            printf("Message : %s\n",mbuf_rcv.mtext);
 int res=strcmp(mbuf_snd.mtext,"bye");
        if(res==10){
                msgctl(msg_id,IPC_RMID,NULL);
      

          printf("queue deleted");
		flag=0;
        exit(0);
  
}
        }
    }
    else
    {
        // Parent is writing
        while(flag==1){
            mbuf_snd.mtype=SEND_KEY;
            printf("Enter the message\n");
            fgets(mbuf_snd.mtext, sizeof mbuf_snd.mtext, stdin);
            if((msgsnd(msg_id,&mbuf_snd,strlen(mbuf_snd.mtext)+1,0))<0)
                perror("msgsnd");
		int res=strcmp(mbuf_snd.mtext,"bye");
	if(res==10){
		msgctl(msg_id,IPC_RMID,NULL);
		printf("queue deleted");
		flag=0;
		exit(0);
}
;
            }
    }
    return 0;
}
