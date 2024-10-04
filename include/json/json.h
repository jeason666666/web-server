#ifndef WEB_JSON_JSON_H
#define WEB_JSON_JSON_H

#include <map>
#include <string>
#include <string_view>

namespace web {
namespace json {

std::map<std::string_view, std::string_view> ParseJson(const std::string_view& json);

std::string DeparseJson(const std::map<std::string_view, std::string_view>& dict);

} // namespace json
} // namespace web

#endif // WEB_JSON_JSON_H
