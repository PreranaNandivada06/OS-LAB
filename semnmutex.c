#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>


long var=0;
int f2();
int f1();
sem_t *sem;
int main()
{
 pthread_t t1,t2;
 sem=sem_open("/iter",O_CREAT,0662,1);
 printf("Parent Thread starts\n"); 
 pid_t chldpid;
 if(fork()){ 
 f1();
 fprintf(stderr, "final var:%ld\n",var);
 }
 else{
 f2();
 }


 
 sem_close(sem);
 sem_unlink("/iter");
 return 0;
}
int f1()
{
  long i;
  for(i=0;i<20;i++){
     sem_wait(sem);
     sleep(1);
     var=var+1;
     sem_post(sem);
     fprintf(stderr, "parent var:%ld\n",var);
  }
  return 0;//return NULL;
}
int f2()
{
  long i;
  for(i=0;i<20;i++){
     sem_wait(sem);
     sleep(1);
     var=var-1;
     sem_post(sem);
     fprintf(stderr, "child var:%ld\n",var);
  }
  return 0;//return NULL;
}
