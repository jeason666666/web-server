#ifndef WEB_SOCKET_HPP
#define WEB_SOCKET_HPP

#include <string_view>

#include <strings.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace web_internal {
namespace net_util {

class Socket {
public:
  Socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
  }

  void Bind(std::string_view& ip, uint16_t port) {
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.data());
    sockaddr.sin_port = htons(port);
  }

  void Listen() {
    listen(fd_, SOMAXCONN);
  }

  int Accept() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(struct sockaddr_in);
    bzero(&client_addr, client_addr_len);

    int client_fd = accept(fd_, (struct sockaddr*)&client_addr, &client_addr_len);

    return client_fd;
  }

  void SetNonBlock() {
    int fd_status = fcntl(fd_, F_GETFD);
    fcntl(fd_, F_SETFD, fd_status | O_NONBLOCK);
  }

private:
  int fd_;

};

} // namespace net_util
} // namespace web_internal

#endif // WEB_SOCKET_HPP