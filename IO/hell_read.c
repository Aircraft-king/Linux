#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){
  int fd=open("myfile",O_RDONLY);
  if(fd < 0){
    perror("OPEN");
    return 1;
  }
  const char *s = "hello world!\n";
  char buf[1024];
  while(1){
    ssize_t a = read(fd,buf,strlen(s));
    if(a > 0){
      printf("%s",buf);
    }
    else{
      break;
    }
  }
  close(fd);
  return 0;
}
