#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>
#include<semaphore.h>
int main()
{  
  sem_t *sem;
  int val;
  int x;
  char *name="/snuc";
  sem=sem_open(name,O_CREAT,0660,5);
  x=sem_getvalue(sem,&val);
  printf("sem value=%d\n",val);  
  sem_wait(sem);
  x=sem_getvalue(sem,&val);
  printf("sem value=%d\n",val); 
  sem_post(sem);  
  x=sem_getvalue(sem,&val);
  printf("sem value=%d\n",val); 
  printf(" Iam here\n");
  sem_close(sem);
  sem_unlink(name);
   return 0;
}
