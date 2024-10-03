#include <iostream>

#include <string_view>

#include "net/http_server.h"
#include "controller.h"

// TODO : ?
using namespace web_internal;

int main()
{
  web_internal::net::HttpServer* http_server = new web_internal::net::HttpServer;

  http_server->Get("/hello", [](const net::Request& req, net::Response& resp){
    resp.SetHeader("Content-Type", "text/html;charset=utf-8");
    resp.SetBody("hello");
  });

  http_server->Post("/api/login", [](const net::Request& req, net::Response& resp){
    std::string out_json;
    web_internal::Controller::ParseLogin(req.body_, &out_json);
    resp.SetHeader("Content-Type", "application/json;charset=utf-8");
    resp.SetBody(out_json);
  });

  http_server->Post("/api/register", [](const net::Request& req, net::Response& resp){
    std::string out_json;
    web_internal::Controller::RegisterAccount(req.body_, &out_json);
    resp.SetHeader("Content-Type", "application/json;charset=utf-8");
    resp.SetBody(out_json);
  });

  http_server->Start();
  return 0;
}