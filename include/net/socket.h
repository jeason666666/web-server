#ifndef WEB_NET_SOCKET_H
#define WEB_NET_SOCKET_H

#include <string_view>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace web {
namespace net {

class Socket {
public:
  Socket();
  explicit Socket(int fd);

  void Bind(const std::string_view& ip, uint16_t port);

  void Listen();

  int Accept();

  void SetNonBlock();

  inline int fd_member_varible() const { return fd_; }

private:
  int fd_;
};

} // namespace net
} // namespace web

#endif // WEB_NET_SOCKET_H