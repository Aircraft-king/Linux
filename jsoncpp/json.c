/*
 * 这个代码主要演示jsoncpp的基本使用序列化和反序列化的过程
 */

#include<cstdio>
#include<iostream>
#include<string>
#include<jsoncpp/json/json.h>
int main(){
  std::string name="小明";
  std::string sex="男";
  int age = 26;
  
  Json::Value value;
  value["姓名"]=name;
  value["性别"]=sex;
  value["年龄"]=age;
  value["成绩"].append(88);
  value["成绩"].append(77);
  value["成绩"].append(99);

  Json::StyledWriter writer;
  std::string json_str = writer.write(value);

  printf("table:%s",json_str.c_str());

  Json::Value val2;
  Json::Reader reader;
  reader.parse(json_str,val2);
  std::cout<<"name:"<<val2["姓名"]<<std::endl;
  std::cout<<"sex:"<<val2["性别"]<<std::endl;
  std::cout<<"age:"<<val2["年龄"]<<std::endl;
  
  std::cout<<"score:"<<val2["成绩"]<<std::endl;
  for(auto it:val2["成绩"])
  {
    std::cout<<"成绩："<<it<<std::endl;
  }
 return 0;
}
