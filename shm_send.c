#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>




int main(){
int id;
int *svar;
key_t key;
key=ftok("shm_recv.c", 8);
id=shmget(key, 128, 0642 | IPC_CREAT);
printf("shm id:%d", id);
svar=(int *)shmat(id, NULL, 0);
*svar=100;
//*svar++;
//*svar=150;
shmdt(svar);
return 0;
}

