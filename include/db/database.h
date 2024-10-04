#ifndef WEB_DB_DATABASE_H
#define WEB_DB_DATABASE_H

#include <string_view>

#include <mysql/mysql.h>

#include "db/sql.h"

namespace web {
namespace db {

class Database {
public:
  Database();
  ~Database();

  void Query(const std::string_view& sql_str);
  MYSQL_RES* Result();

private:
  MYSQL* mysql_ = nullptr;
};

} // namespace db
} // namespace web


#endif // WEB_DB_DATABASE_H