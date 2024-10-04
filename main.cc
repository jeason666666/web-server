#include "controller.h"
#include "httplib.h"

#include <iostream>

int main()
{
  httplib::Server svr;
  
  svr.Post("/api/login", [](const httplib::Request& req, httplib::Response &resp) {
    // TODO : log
    std::cout << "post login" << '\n';

    std::string out_json;
    web::Controller::ParseLogin(req.body, &out_json);
    resp.set_content(out_json, "application/json;charset=utf-8");
  });
  
  svr.Post("/api/register", [](const httplib::Request& req, httplib::Response &resp) {
    // TODO : register
    std::cout << "post register" << '\n';

    std::string out_json;
    web::Controller::RegisterAccount(req.body, &out_json);
    resp.set_content(out_json, "application/json;charset=utf-8");
  });

  svr.listen("0.0.0.0", 8080);
  
  return 0;
}
