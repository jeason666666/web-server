#include "controller.h"
#include "json/json.h"

#include <iostream>

namespace web {

Controller* Controller::inst_ = new Controller();
db::Database Controller::database_ = db::Database();

const static char* CHARSET  = "utf-8";

Controller::Controller()
{
}

Controller::~Controller()
{
}

std::string Controller::ParseLogin(const std::string_view& in_json, std::string* out_json)
{
  std::map<std::string_view, std::string_view> in_dict 
    = json::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  // TODO : 封装 mysql 查询语句，使用RAII
  // TODO : mysql调优，避免使用select* ?
  std::string sql = "SELECT username, password FROM users";
  database_.Query(sql);

  MYSQL_RES* res = database_.Result();
  
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

  *out_json = json::DeparseJson(out_dict); 
  return json::DeparseJson(out_dict);
}

void Controller::RegisterAccount(const std::string_view& in_json, std::string* out_json)
{
  std::map<std::string_view, std::string_view> in_dict 
    = json::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  std::string sql = "INSERT users (username, password) VALUE ('";
  sql += in_dict["username"];
  sql += "',";
  sql += in_dict["password"];
  sql += ')';

  std::cout << sql << '\n';

  database_.Query(sql);

  out_dict.insert({"status", "success"});
  *out_json = json::DeparseJson(out_dict);
}

} // namespace web_internal
