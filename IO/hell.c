#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){
  umask(0);
  int fd=open("myfile",O_WRONLY|O_CREAT,0664);
  if(fd < 0){
    perror("OPEN");
    return 1;
  }
  int count = 5;
  const char *s = "hello world\n";
  int len = strlen(s);
  while(count--){
    write(fd,s,len);
  }
  close(fd);

  return 0;
}
