#include "controller.h"
#include "json_helper.h"

namespace web_internal {

std::string Controller::ParseLogin(const std::string_view& in_json, std::string* out_json)
{
  std::map<std::string_view, std::string_view> in_dict = json_util::ParseJson(in_json);
  std::map<std::string_view, std::string_view> out_dict;

  // TODO :
  // 验证 账号密码

  if (in_dict["username"] == "ljs" && in_dict["password"] == "123321") {
    out_dict.insert({"status","success"});
  } else {
    out_dict.insert({"status", "fail"});
  }

  return json_util::DeparseJson(out_dict);
}

} // namespace web_internal
