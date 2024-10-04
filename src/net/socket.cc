#include "net/socket.h"

#include <strings.h>

#include "log/log.h"

namespace web {
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
  ASSERT(
    bind(fd_, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) != -1
    );
}

void Socket::Listen()
{
  ASSERT(
    listen(fd_, SOMAXCONN) != -1
    );
}

int Socket::Accept()
{
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  bzero(&client_addr, client_addr_len);

  return accept(fd_, (struct sockaddr*)&client_addr, &client_addr_len);
}

void Socket::SetNonBlock()
{
  int fd_status = fcntl(fd_, F_GETFL);
  fcntl(fd_, F_SETFL, fd_status | O_NONBLOCK);
}

} // namespace net
} // namespace web
