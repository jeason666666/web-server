#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <string>
#include <string_view>

#include <mysql/mysql.h>

#include "db/database.h"

namespace web {

class Controller {
public:
  Controller();
  ~Controller();

  static std::string ParseLogin(const std::string_view& in_json, std::string* out_json);

  static void RegisterAccount(const std::string_view& in_json, std::string* out_json);

  static Controller* Instance() { return inst_; }

private:
  static Controller* inst_;
  
  static db::Database database_;
};

} // namespace web

#endif // WEB_CONTROLLER_H
