#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main(){
  int i = 0;
  for(i=0; i<256; ++i){
    sleep(1);
    printf("errmsg:[%s]\n",strerror(i));
  }
  exit(0);
  return 0;
}
