#include <iostream>

#include "json_helper.h"

int main()
{
  std::string str = R"({"username":"ljs", "password":"123321"})";
  auto mp = web_internal::json_util::ParseJson(str);
  for (auto&[k, v] : mp) {
    std::cout << k << ':' << v << '\n';
  }
  return 0;
}
