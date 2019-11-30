#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(){
    while(1){
      cout<<"process:"<<getpid()<<"parent:"<<getppid()<<endl;
      sleep(1);
    }
    return 0;
}
