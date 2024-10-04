#include "db/sql.h"

#include <mysql/mysql.h>

#include "log/log.h"

namespace web {
namespace db {

Sql::Sql(MYSQL* mysql, const std::string_view& sql)
  : mysql_(mysql)
  , sql_(sql)
{
  ASSERT(!sql_.empty());
}

void Sql::Query()
{
  ASSERT(mysql_query(mysql_, sql_.c_str()) == 0);
}

} // namespace db
} // namespace web
