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
    std::cout << "post api login\n";
  });
  
  svr.listen("0.0.0.0", 8080);
  
  return 0;
}
