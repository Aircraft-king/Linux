#include"order_system.hpp"
#include"httplib.h"

_order_sys::DishTable *dish_table;
_order_sys::OrderTable *order_table;

void InsertDish(const httplib::Request &req,httplib::Response &rsp){
  //req.body(正文)
  Json::Value dish_val;
  Json::Reader reader;
  bool ret = reader.parse(req.body,dish_val);
  if(ret==false){
    std::cout<<"InsertDish parse failed!!!\n";
    rsp.status = 400;
  }
  ret = dish_table->Insert(dish_val);
  if(ret == false){
    rsp.status=500;
    return;
  }
  rsp.status = 200;
  return;
}
void DeleteDish(const httplib::Request &req,httplib::Response &rsp){
  int dish_id = std::stoi(req.matches[1]);
  bool ret = dish_table->Delete(dish_id);
  if(ret ==false){
    std::cout<<"DeleteDish error"<<std::endl;
    rsp.status = 500;
    return;
  }
  rsp.status=200;
  return;
}
void UpdateDish(const httplib::Request &req,httplib::Response &rsp){
  Json::Value dish_val;
  Json::Reader reader;
  bool ret = reader.parse(req.body,dish_val);
  if(ret == false){
    rsp.status = 400;
    return;
  }
  ret = dish_table->Update(dish_val);
    if(ret == false){
      rsp.status = 500;
      return;
    }
  rsp.status = 200;
  return;
}
void SelectOnedish(const httplib::Request &req,httplib::Response &rsp){
  int dish_id = std::stoi(req.matches[1]);
  Json::Value dish_val;
  bool ret =dish_table->SelectOne(dish_id,&dish_val);
  if(ret == false){
    rsp.status = 500;
    return;
  }
  Json::FastWriter writer;
  std::string body = writer.write(dish_val);

  rsp.set_content(body.c_str(),body.size(),"application/json");
  rsp.status = 200;
  
  return;
}
void SelectAlldish(const httplib::Request &req,httplib::Response &rsp){
  Json::Value dishes_val;
  bool ret = dish_table->SelectAll(&dishes_val);
  if(ret == false){
    rsp.status = 500;
    return;
  }
  std::string body;
  Json::FastWriter writer;
  body = writer.write(dishes_val);

  rsp.set_content(body.c_str(),body.size(),"application/json");
  rsp.status = 200;
  return;
}
void InsertOrder(const httplib::Request &req,httplib::Response &rsp){
  Json::Value order_val;
  Json::Reader reader;

  bool ret = reader.parse(req.body,order_val);
  if(ret == false){
    rsp.status = 400;
    return;
  }
  ret = order_table->Insert(order_val);
  if(ret == false){
    rsp.status = 500;
    return;
  }
  rsp.status = 200;
  return;
}
void DeleteOrder(const httplib::Request &req,httplib::Response &rsp){
  int order_id = std::stoi(req.matches[1]);
  bool ret = order_table->Delete(order_id);
  if(ret == false){
    rsp.status = 500;
    return;
  }
  rsp.status = 200;
  return;
}
void UpdateOrder(const httplib::Request &req,httplib::Response &rsp){
  Json::Value order_val;
  Json::Reader reader;
  bool ret = reader.parse(req.body,order_val);
  if(ret == false){
    rsp.status = 400;
    return;
  }
  ret = order_table->Update(order_val);
  if(ret == false){
    return;
  }
  rsp.status = 200;
  return;
}
void SelectOneOrder(const httplib::Request &req,httplib::Response &rsp){
  int order_id = std::stoi(req.matches[1]);
  Json::Value order_val;
  bool ret = order_table->SelectOne(order_id,&order_val);
  if(ret == false){
    return;
  }
  std::string body;
  Json::FastWriter writer;
  body = writer.write(order_val);
  rsp.set_content(body.c_str(),body.size(),"application/json");
  rsp.status = 200;
  return;
}
void SelectAllOrder(const httplib::Request &req,httplib::Response &rsp){
  Json::Value order_val;
  bool ret = order_table->SelectAll(&order_val);
  if(ret == false){
    return;
  }
  std::string body;
  Json::FastWriter writer;
  body = writer.write(order_val);
  rsp.set_content(body.c_str(),body.size(),"application/json");
  rsp.status = 200;
  return;
}

#define CLIENT_CODE "./client_code"

int main(){
  MYSQL *mysql = _order_sys::MYsqlInit();
  dish_table = new _order_sys::DishTable(mysql);
  order_table = new _order_sys::OrderTable(mysql);

  httplib::Server server;
  //插入菜品请求 POST
  server.Post("/dish",InsertDish);
  //删除菜品请求 DELETE
  server.Delete(R"(/dish/(\d+))",DeleteDish);
  //更新菜品请求 PUT
  server.Put("/dish",UpdateDish);
  //查询单个菜品请求 GET
  server.Get(R"(/dish/(\d+))",SelectOnedish);
  //查询所有菜品请求 GET
  server.Get("/dish",SelectAlldish);
  //订单信息增删改查
  server.Post("/order",InsertOrder);
  server.Delete(R"(/order/(\d+))",DeleteOrder);
  server.Put("/order",UpdateOrder);
  server.Get(R"(/order/(\d+))",SelectOneOrder);
  server.Get("/order",SelectAllOrder);
  server.set_base_dir(CLIENT_CODE);
  server.listen("0.0.0.0",9000);
  _order_sys::MysqlDestroy(mysql);



  /////////////////////////////////////////////////////////
  /* MYSQL *mysql = _order_sys::MYsqlInit();
     if(mysql==NULL){
     return -1;
     }
     _order_sys::DishTable dish_tb(mysql);
     _order_sys::OrderTable order_tb(mysql);
     */
  /* 插入菜品测试
     Json::Value dish;
     dish["name"]="红烧肉";
     dish["price"]=3600;
     dish_tb.Insert(dish);
     */
  /*查询单个菜品信息
    Json::Value dish1;
    Json::StyledWriter writer;
    dish_tb.SelectOne(3,&dish1);
    std::cout<<"dish"<<writer.write(dish1)<<std::endl;
    _order_sys::MysqlDestroy(mysql);
    */
  /*查询所有菜品信息
    Json::Value dish2;
    Json::StyledWriter writer2;
    dish_tb.SelectAll(&dish2);
    std::cout<<"dish_all"<<writer2.write(dish2)<<std::endl;
    */
  /*更新菜品信息
    Json::Value dish3;
    dish3["id"]=4;
    dish3["name"]="唐僧肉";
    dish3["price"]=5800;
    dish_tb.Update(dish3);
    */
  /*删除菜品信息
    dish_tb.Delete(4);
    */
  /* 
     Json::Value order;
     Json::StyledWriter writer;
     */
  /* 插入订单
     order["table_id"] =  3;
     order["dishes"].append(1);
     order["status"] = 0;
     order_tb.Insert(order);
     */
  /*查询单个订单 
    Json::Value order1;
    order_tb.SelectOne(1,&order1);
    std::cout<<"order:"<<writer.write(order1);
    */
  /*查询所有订单
    order_tb.SelectAll(&order);
    std::cout<<"order:"<<writer.write(order);
    */
  /*更新订单信息
    order["id"] =  1;
    order["table_id"] =  2;
    order["dishes"].append(3);
    order["dishes"].append(1);
    order["status"] = 0;
    order_tb.Update(order);
    */
  /*删除订单信息
    order_tb.Delete(2);
    */
  return 0;
}
