#ifndef WEB_JSON_READER_H
#define WEB_JSON_READER_H

#include <map>
#include <string>
#include <string_view>

namespace web_internal {
namespace json_util {

std::map<std::string_view, std::string_view> ParseJson(const std::string_view& json);

std::string DeparseJson(const std::map<std::string_view, std::string_view>& dict);

} // namespace json_util
} // namespace web_internal

#endif // WEB_JSON_READER_H
