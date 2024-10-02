#include "net/socket.h"

#include <strings.h>

namespace web_internal {
namespace net {

Socket::Socket()
{
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int fd)
  : fd_(fd)
{

}

void Socket::Bind(const std::string_view& ip, uint16_t port)
{
  struct sockaddr_in sockaddr;
  bzero(&sockaddr, sizeof(struct sockaddr_in));
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = inet_addr(ip.data());
  sockaddr.sin_port = htons(port);
  bind(fd_, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
}

void Socket::Listen()
{
  listen(fd_, SOMAXCONN);
}

int Socket::Accept()
{
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(struct sockaddr_in);
  bzero(&client_addr, client_addr_len);

  return accept(fd_, (struct sockaddr*)&client_addr, &client_addr_len);
}

void Socket::SetNonBlock()
{
  int fd_status = fcntl(fd_, F_GETFL);
  fcntl(fd_, F_SETFL, fd_status | O_NONBLOCK);
}

} // namespace net
} // namespace web_internal
