#include "logger/log.h"

#include <cstdio>
#include <string>

namespace web_internal {
namespace log {

void Log(LogLevel log_level, const std::string& log_str)
{
  Log(log_level, __FILE__, __LINE__, log_str);
}

void Log(LogLevel log_level, const char* file_name, const int line_num
  , const std::string& log_str)
{
  std::string level_str;
  if      (log_level == LogLevel::kDebug) level_str = "DEBUG";
  else if (log_level == LogLevel::kInfo)  level_str = "INFO";
  else if (log_level == LogLevel::kWarn)  level_str = "WARN";
  else if (log_level == LogLevel::kError) level_str = "ERROR";
  else if (log_level == LogLevel::kFatal) level_str = "FATAl";

  printf("[%s] %s:%d : %s\n"
    , level_str.c_str(), file_name, line_num, log_str.data());
}

} // namespace log
} // namespace web_internal
