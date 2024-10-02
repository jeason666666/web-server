#ifndef WEB_LOGGER_LOG_H
#define WEB_LOGGER_LOG_H

#include <string_view>

namespace web_internal {
namespace log {

#define LOG(log_level, log_str) do { \
  Log(log_level, __FILE__, __LINE__, log_str); \
} \
while (0)

enum class LogLevel {
  kDebug = 0,
  kInfo = 1,
  kWarn = 2,
  kError = 3,
  kFatal = 4
};

void Log(LogLevel log_level, const std::string_view& log_str);

void Log(LogLevel log_level, const char* file_name, const int line_num
  , const std::string_view& log_str);

} // namespace log
} // namespace web_internal

#endif // WEB_LOGGER_LOG_H
