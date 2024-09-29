#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <string>
#include <string_view>

#include <mysql/mysql.h>

namespace web_internal {

class Controller {
public:
  Controller();
  ~Controller();

  static std::string ParseLogin(const std::string_view& in_json, std::string* out_json);

  static void RegisterAccount(const std::string_view& in_json, std::string* out_json);

  static Controller* Instance() { return inst_; }

  MYSQL* Mysql() { return mysql_; }

private:
  static Controller* inst_;

private:
  MYSQL* mysql_ = nullptr;
};

} // namespace web_internal

#endif // WEB_CONTROLLER_H
