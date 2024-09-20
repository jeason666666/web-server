#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <string>
#include <string_view>

namespace web_internal {

class Controller {
public:
  static std::string ParseLogin(const std::string_view& in_json, std::string* out_json);
private:
};

} // namespace web_internal

#endif // WEB_CONTROLLER_H
