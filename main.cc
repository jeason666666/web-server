#include "controller.h"
#include "httplib.h"
#include "json_helper.h"

#include <iostream>

int main()
{
  httplib::Server svr;
  
  svr.Post("/api/login", [](const httplib::Request& req, httplib::Response &resp) {
    resp.set_content("Hello World!", "content-type: text/plain;");
    std::cout << req.body << '\n';
    // TODO : log
    std::string out_json;
    web_internal::Controller::ParseLogin(req.body, &out_json);
    resp.set_content(out_json, "Content-Type:application/json");
    std::cout << "post api login\n";
  });
  
  svr.listen("0.0.0.0", 8080);
  
  return 0;
}
