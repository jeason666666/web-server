#include "controller.h"
#include "json_helper.h"

#include <iostream>

namespace web_internal {

Controller* Controller::inst_ = new Controller();

// mysql 登陆参数
// TODO : 避免明文验证
const static char* HOST     = "127.0.0.1";
const static char* USER     = "root";
const static char* PASSWORD = "123456";
const static char* DATABASE = "web";
const static uint16_t PORT  = 3306;

const static char* CHARSET  = "utf-8";

Controller::Controller()
{
  // TODO : 改为RAII
  mysql_ = mysql_init(nullptr);
  if (mysql_ == nullptr) {

  }

  mysql_real_connect(mysql_, HOST, USER, PASSWORD, DATABASE, PORT, nullptr, 0);

  mysql_set_character_set(mysql_, CHARSET);
}

Controller::~Controller()
{
  mysql_close(mysql_);
}

std::string Controller::ParseLogin(const std::string_view& in_json, std::string* out_json)
{
  std::map<std::string_view, std::string_view> in_dict = json_util::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  // TODO : 封装 mysql 查询语句，使用RAII
  // TODO : mysql调优，避免使用select* ?
  std::string sql = "select username, password from users";
  // TODO : 优化获取 MYSQL 指针的方式
  mysql_query(Instance()->Mysql(), sql.c_str());

  MYSQL_RES* res = mysql_store_result(Instance()->mysql_);
  
  uint64_t num_row = mysql_num_rows(res);
  int num_col = mysql_num_fields(res);
  // TODO : 优化一下多嵌套
  for (int i = 0; i < num_row; i ++) {
    MYSQL_ROW row = mysql_fetch_row(res);
    for (int j = 0; j < num_col; j ++) {
      std::cout << row[j] << ' ';
    } std::cout << '\n';
    std::string username = row[0], password = row[1];
    std::cout << in_dict["username"] << " " << in_dict["password"] << '\n';
    if (in_dict["username"] == username && in_dict["password"] == password) {
      std::cout << "success\n";
      out_dict.insert({"status","success"});
    }
  }

  // 没有该用户
  if (!out_dict.count("status")) {
    out_dict.insert({"status", "fail"});
  }
  return json_util::DeparseJson(out_dict);
}

} // namespace web_internal
