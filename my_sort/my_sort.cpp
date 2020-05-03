#include<iostream>
using namespace std;

void my_sort(int *arr,int low,int high){
  if(low>=high) return;
  int i = low;
  int j = high+1;
  int key = arr[low];
  while(low<high){
    while(arr[++i]<key){
      if(i==high)
        break;
    }
    while(arr[--j]>key){
      if(j==low)
        break;
    }
    if(i>=j) break;
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  } 
  int tmp = arr[low];
  arr[low] = arr[j];
  arr[j] = tmp;
  my_sort(arr,low,j-1);
  my_sort(arr,j+1,high);
}

int main(){

  int arr[10]={9,8,7,6,5,4,3,2,1,0};
  my_sort(arr,0,9);
  for(int i=0;i<10;++i){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
  return 0;
}
