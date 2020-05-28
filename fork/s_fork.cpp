#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
int main(){
  pid_t pid;
  printf("before: pid is %d\n",getpid());
  if((pid=fork())==-1){
    perror("fork()");
    exit(1);
  }
  printf("after: pid is %d,fork return %d\n",getpid(),pid);
  sleep(1);
  return 0;
}
