#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
  int fds[2];
  char buf[100];
  int len;

  if(pipe(fds)==-1){
    perror("make pipe fail");
    return -1;
  }
  
  while(fgets(buf,100,stdin)){
    len = strlen(buf);
    //往管道中写文件
    if(write(fds[1],buf,len)!=len){
      perror("write pipe");
      break;
    }
    memset(buf,0x00,sizeof(buf));
    //读文件
    if((len = read(fds[0],buf,100))==-1){
      perror("read pipe");
      break;
    }
    
    if(write(1,buf,len)!=len){
      perror("write stdout");
      break;
    }
  }
  return 0;
}
