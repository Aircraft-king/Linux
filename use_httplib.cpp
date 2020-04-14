#include<iostream>
#include"httplib.h"

void HelloWorld(const httplib::Request &req,httplib::Response &rsp){
  std::cout<<"method"<<req.method<<std::endl;
  std::cout<<"path"<<req.path<<std::endl;
  std::cout<<"body"<<req.body<<std::endl;
  rsp.status=200;
  rsp.body="<html><body><h1>HelloWorld</h1></body></html>";
  rsp.set_header("Content-type","text/html");
  return;
}

int main(){
  int a=100;
  httplib::Server server;
  server.Get("/hello",HelloWorld);
  server.Get("/hi",[&](const httplib::Request &req,httplib::Response &rsp){
      std::cout<<"a:"<<a<<std::endl;
      std::string body = "<html><body><h1>hi plmm</h1></body></html>";
      rsp.set_content(body.c_str(),body.size(),"text/html");

      });

  server.listen("0.0.0.0",9000);

  return 0;
}
