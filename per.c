#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(){
  open("/etc/passwd", O_RDWR|O_CREAT,S_IRUSR);
  int x = errno;
  perror("hi: ");
  printf("hello %d\n",x);
  
  fprintf(stdout, "good\n");
  fprintf(stderr, "bye\n");

  write(1, "great\n",6);
  write(2, "good bye\n",9);
}
