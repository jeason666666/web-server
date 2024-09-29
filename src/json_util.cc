#include "json_util.h"

#include <iostream>
#include <vector>

namespace web_internal {
namespace json_util {

std::map<std::string_view, std::string_view> ParseJson(const std::string_view& json)
{
  // {"uesrname":"ljs", "password":"123"}
  std::map<std::string_view, std::string_view> res;
  std::vector<size_t> poss;
  
  for (size_t pos = 0; pos != std::string_view::npos;) {
    
    pos = json.find('"', pos);
    if (pos != std::string_view::npos) {
      poss.emplace_back(pos);
      pos++;
    }

  }
  for (size_t count = 0; count < poss.size() / 4; count++) {
    
    size_t key_pos = poss[count * 4] + 1, 
           key_len = poss[count * 4 + 1] - poss[count * 4] - 1;
    size_t value_pos = poss[count * 4 + 2] + 1, 
           value_len = poss[count * 4 + 3] - poss[count * 4 + 2] - 1;
    
    res.insert({json.substr(key_pos, key_len), 
                json.substr(value_pos, value_len)});   
  }

  return res;
}

std::string DeparseJson(const std::map<std::string_view, std::string_view>& dict)
{
  std::string json = "{";

  // {"uesrname":"ljs", "password":"123"}
  for (auto& [key, value] : dict) {
    json += '"';
    json += key;
    json += R"(":")";
    json += value;
    json += '"';
  }

  json += '}';

  return json;
}

} // namespace json_util
} // namespace web_internal
