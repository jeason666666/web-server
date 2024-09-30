#ifndef WEB_DB_UTIL_H
#define WEB_DB_UTIL_H

#include <mysql/mysql.h>

#include <string_view>

namespace web_internal {
namespace db_util {

class DataBase {
public:
  DataBase();
  ~DataBase();

  void SetDataBase(const std::string_view& database_name);

  

private:
  MYSQL* mysql_;
};

} // namespace db_util
} // namespace web_internal

#endif // WEB_DB_UTIL_H
