#include <iostream>

#include <net/tcp_server.h>
#include <string_view>

int main()
{
  web_internal::net::TcpServer* tcp_server = new web_internal::net::TcpServer;
  tcp_server->Start();
  return 0;
}