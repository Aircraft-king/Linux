/*
 * 通过c语言接口实现my_sql基本操作
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main(){

  MYSQL *mysql = mysql_init(NULL);
 if( mysql_real_connect(mysql,"127.0.0.1","root",NULL,"db_order_sys",0,NULL,0)==NULL){
   printf("mysql connect failed:%s\n",mysql_error(mysql));
   return -1;
 }
 int ret = mysql_set_character_set(mysql,"utf8");
 if(ret!=0){
   printf("set character to utf8 failed:%s\n",mysql_error(mysql));
   return -1;
 }
  char *sql_str = "select * from tb_dishes;";
  ret = mysql_query(mysql, sql_str);
  if(ret!=0){
    printf("sql query failed:%s\n",mysql_error(mysql));
    return -1;
  }
  MYSQL_RES *res = mysql_store_result(mysql);
  if(res == NULL){
    printf("store result failed:%s\n",mysql_error(mysql));
    return -1;
  }
  int row_nums = mysql_num_rows(res);
  int col_nums = mysql_num_fields(res);
  int i = 0;
  int j = 0;
  for(;i<row_nums; ++i){
    MYSQL_ROW row = mysql_fetch_row(res);
    for(j=0; j<col_nums;j++){
       printf("%-8s",row[j]);
    }
    printf("\n");
  }
  mysql_free_result(res);
  mysql_close(mysql);
  return 0;
}
