#ifndef WEB_NET_EPOLL_H
#define WEB_NET_EPOLL_H

#include <sys/epoll.h>

#include <set>
#include <vector>

#include "net/socket.h"

namespace web_internal {
namespace net {

static const int kMaxEventNum = 1024;

class Epoll {
public:
  Epoll();

  void SetEvent(const Socket& socket, int op);
  void RemoveSocket(const Socket& socket);
  std::vector<struct epoll_event> Wait();

private:
  int epoll_fd_;
  struct epoll_event events_[kMaxEventNum];
  std::set<int> epoll_fds_;
};

} // namespace net
} // namespace web_internal

#endif // WEB_NET_EPOLL_H
