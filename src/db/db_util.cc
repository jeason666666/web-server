#include "db/db_util.h"

namespace web_internal {
namespace db_util {

const static char* HOST     = "127.0.0.1";
const static char* USER     = "root";
const static char* PASSWORD = "123456";
const static char* DATABASE = "web";
const static uint16_t PORT  = 3306;

const static char* CHARSET  = "utf-8";

DataBase::DataBase()
{
  mysql_ = mysql_init(nullptr);
  if (mysql_ == nullptr) {

  }

  mysql_real_connect(mysql_, HOST, USER, PASSWORD, DATABASE, PORT, nullptr, 0);
  mysql_set_character_set(mysql_, CHARSET);
}

DataBase::~DataBase()
{
  mysql_close(mysql_);
}

void DataBase::SetDataBase(const std::string_view& database_name)
{
  mysql_select_db(mysql_, database_name.data());
}

} // namespace db_util
} // namespace web_internal
