#include "db/database.h"

#include <stdint.h>

#include <memory>

namespace web {
namespace db {

// mysql 登陆参数
// TODO : 避免明文验证
const static char* kHost     = "127.0.0.1";
const static char* kUser     = "root";
const static char* kPassword = "123456";
const static char* kDatabase = "web";
const static uint16_t kPort  = 3306;

const static char* kCharset  = "utf-8";

Database::Database()
{
  mysql_ = mysql_init(nullptr);
  if (mysql_ == nullptr) {

  }

  mysql_real_connect(mysql_, kHost, kUser, kPassword, kDatabase, kPort, nullptr, 0);
  mysql_set_character_set(mysql_, kCharset);
}

Database::~Database()
{
  mysql_close(mysql_);
}

void Database::Query(const std::string_view& sql_str)
{
  std::unique_ptr<Sql> sql(new Sql(mysql_, sql_str));
  sql->Query();
}

MYSQL_RES* Database::Result()
{
  return mysql_store_result(mysql_);
}

} // namespace db
} // namespace web
