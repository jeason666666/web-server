#ifndef WEB_NET_HTTP_SERVER_H
#define WEB_NET_HTTP_SERVER_h

#include "net/http.h"
#include "net/tcp_server.h"

#include <functional>
#include <map>
#include <string>

namespace web {
namespace net {

using Handler = std::function<void(const Request&, Response&)>;

class HttpServer : public TcpServer {
public:
  void Recver(Connection* connection) override;

  void Sender(Connection* connection) override;

  void Get(const std::string& path, Handler&& handler);

  void Post(const std::string& path, Handler&& handler);

private:
  std::map<std::string, Handler> get_method_mp_;
  std::map<std::string, Handler> post_method_mp_;
};

} // namespace net
} // namespace web

#endif // WEB_NET_HTTP_SERVER_H
