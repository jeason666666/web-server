#ifndef WEB_LOGGER_LOG_H
#define WEB_LOGGER_LOG_H

#include <string>

namespace web {
namespace log {

#define LOG(log_level, log_str) do { \
  Log(log_level, __FILE__, __LINE__, log_str); \
} \
while (0)

#define ASSERT(condition) do { \
  log::Assert(#condition, condition, __FILE__, __LINE__); \
} \
while (0)

enum LogLevel {
  kDebug = 0,
  kInfo = 1,
  kWarn = 2,
  kError = 3,
  kFatal = 4
};

void Log(LogLevel log_level, const std::string& log_str);

void Log(LogLevel log_level, const char* file_name, const int line_num
  , const std::string& log_str);

void Assert(const char* file_name, const int line_num
  , const char* condition_str, bool Condition);

} // namespace log
} // namespace web

#endif // WEB_LOGGER_LOG_H
