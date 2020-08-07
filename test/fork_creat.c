#include<stdio.h>
#include<unistd.h>
int a = 0;
int main(){
  for(int i=0;i<3;i++){
    fork();
    printf("*\n");
    a++;
  }
  printf("%d",a);
  return 0;
}
