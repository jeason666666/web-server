#include "controller.h"
#include "json_util.h"

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
  std::map<std::string_view, std::string_view> in_dict 
    = json_util::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  // TODO : 封装 mysql 查询语句，使用RAII
  // TODO : mysql调优，避免使用select* ?
  std::string sql = "SELECT username, password FROM users";
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
    if (in_dict["username"] == username && in_dict["password"] == password) {
      std::cout << "success\n";
      out_dict.insert({"status", "success"});
    }
  }

  mysql_free_result(res);

  // 没有该用户
  if (!out_dict.count("status")) {
    std::cout << "fail" << '\n';
    out_dict.insert({"status", "fail"});
  }

  *out_json = json_util::DeparseJson(out_dict); 
  return json_util::DeparseJson(out_dict);
}

void Controller::RegisterAccount(const std::string_view& in_json, std::string* out_json)
{
  std::map<std::string_view, std::string_view> in_dict 
    = json_util::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  std::string sql = "INSERT users (username, password) VALUE ('";
  sql += in_dict["username"];
  sql += "',";
  sql += in_dict["password"];
  sql += ')';

  std::cout << sql << '\n';
  bool success = mysql_query(Instance()->Mysql(), sql.c_str()) == 0;

  if (success) {
    out_dict.insert({"status", "success"});
  } else {
    out_dict.insert({"status", "fail"});
  }

  *out_json = json_util::DeparseJson(out_dict);
}

} // namespace web_internal
