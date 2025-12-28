// C Program for Message Queue (Writer Process) 
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


// structure for message queue 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[20]; 
} message; 


int main() 
{ 
	key_t key; 
	int msgid; 


	// ftok to generate unique key 
	key = ftok("msgrcv.c", 65); 


	// msgget creates a message queue 
	// and returns identifier 
	msgid = msgget(key, 0600 | IPC_CREAT); 
	printf("Message Queue ID: %d\n", msgid);
	message.mesg_type = 1; 


	printf("Write Data : "); 
	fgets(message.mesg_text, sizeof(message.mesg_text), stdin);




	// msgsnd to send message 
	msgsnd(msgid, &message, sizeof(message), 0); 


	// display the message 
	printf("Data send is : %s \n", message.mesg_text); 


	return 0; 
} 

