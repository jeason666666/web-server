#include "net/epoll.h"

#include "logger/log.h"

namespace web_internal {
namespace net {

Epoll::Epoll()
{
  epoll_fd_ = epoll_create(1024);
}

void Epoll::SetEvent(const Socket& socket, int op)
{
  int fd = socket.fd_member_varible();
  struct epoll_event event;
  event.data.fd = fd;
  event.events = op;
  if (!epoll_fds_.count(fd)) {
    LOG(log::LogLevel::kDebug, "epoll add event");
    epoll_fds_.insert(fd);
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event);
  } else {
    LOG(log::LogLevel::kDebug, "epoll modify event");
    epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event);
  }
}

void Epoll::RemoveSocket(const Socket& socket)
{
  int fd = socket.fd_member_varible();
  if (!epoll_fds_.count(fd)) {
    LOG(log::LogLevel::kDebug, "epoll remove event");
    epoll_fds_.erase(fd);
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr);
  }
}

std::vector<struct epoll_event> Epoll::Wait()
{
  int n = epoll_wait(epoll_fd_, events_, kMaxEventNum, 0);
  if (n > 0) {
    LOG(log::LogLevel::kDebug, "epoll wait : some new event come");
  }
  std::vector<struct epoll_event> ready_events;
  for (int i = 0; i < n; i ++) {
    ready_events.push_back(events_[i]);
  }
  return ready_events;
}

} // namespace net
} // namespace web_internal
