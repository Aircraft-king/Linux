#include<stdio.h>

int main(int argc , char *argv[], char *env[]){

  int i = 0;
  for( ; env[i]; ++i ){
    printf("%d--%s\n ",i,env[i]);
  }
  printf("\n");
  return 0;
}
