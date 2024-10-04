#ifndef WEB_DB_SQL_H
#define WEB_DB_SQL_H

#include <string>
#include <string_view>

#include <mysql/mysql.h>

namespace web {
namespace db {

struct Sql {
  Sql(MYSQL* mysql, const std::string_view& sql);

  // execute sql
  void Query();

  MYSQL* mysql_;
  std::string sql_;
};

} // namespace db
} // namespace web

#endif // WEB_DB_SQL_H
