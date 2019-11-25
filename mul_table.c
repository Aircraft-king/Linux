#include<stdio.h>

int main(){

  int i = 0;
  int j = 0;
  int n = 0;
  printf("请输入乘法表的大小：>");
  scanf("%d",&n);
  for(i=1 ;i<=n; ++i){
    for(j=1; j<=i; ++j){
      printf("%2d *%2d=%3d ",i,j,i*j);
    }
    printf("\n");
  }
  return 0;
}
