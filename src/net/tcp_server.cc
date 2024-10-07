#include "net/tcp_server.h"

#include <string.h>

#include <cerrno>
#include <cstdio>

#include "log/log.h"

namespace web {
namespace net {

static const int kBufferNum = 1024;

Connection::Connection(const Socket& socket)
  : socket_(socket)
  , read_cb_(nullptr)
  , write_cb_(nullptr)
  , except_cb_(nullptr)
{
}

void Connection::SetCallback
  (BindCallback read_cb, BindCallback write_cb, BindCallback except_cb)
{
  read_cb_ = read_cb;
  write_cb_ = write_cb;
  except_cb_ = except_cb;
}

TcpServer::TcpServer(long int time_out)
  : epoll_()
  , listen_socket_()
  , timer_(time_out)
{
  LOG(log::LogLevel::kDebug, "tcp server finish init");
}

TcpServer::~TcpServer()
{
  for (auto& [fd, connection] : connections_) {
    delete connection;
    // TODO : 可以封装一个函数
    // 从epoll中移除该监听事件
  }
}

void TcpServer::Start()
{
  listen_socket_.Bind(kIp, kPort);
  listen_socket_.Listen();
  listen_socket_.SetNonBlock();
  // TODO : 重载函数
  Connection* listen_connection = new Connection(Socket(listen_socket_.fd_member_varible()));
  connections_[listen_socket_.fd_member_varible()] = listen_connection;
  listen_connection->SetCallback
    ( std::bind(&TcpServer::Accepter, this, listen_connection)
    , nullptr
    , nullptr);

  epoll_.SetEvent(listen_socket_, EPOLLIN | EPOLLET);
  
  LOG(log::LogLevel::kInfo, "tcp server start loop");
  while (true) {
    LoopOnce();
  }
}

void TcpServer::LoopOnce()
{
  std::vector<struct epoll_event> ready_events = epoll_.Wait();
  for (auto& event : ready_events) {
    int fd = event.data.fd;

    ASSERT(connections_.count(fd));
    LOG(log::LogLevel::kDebug, "new event");

    if (event.events & EPOLLIN) {
      ASSERT(connections_[fd]->read_cb_ != nullptr);
      thread_pool_.AddTask(connections_[fd]->read_cb_);
    } else if (event.events & EPOLLOUT) {
      ASSERT(connections_[fd]->write_cb_ != nullptr);
      thread_pool_.AddTask(connections_[fd]->write_cb_);
    }
  }
}

void TcpServer::Accepter(Connection* connection)
{
  LOG(log::LogLevel::kDebug, "accept new connection");
  RemoveOverTimeConnection();
  while (true) {
    LOG(log::LogLevel::kDebug, "try to accept");
    int new_fd = connection->socket_member_variable().Accept();
    if (new_fd == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        break;
      } else if (errno == EINTR) {
        continue;
      } else {
        log::Log(log::LogLevel::kFatal, strerror(errno));
        // TODO : 可以给专门的错误吗
        exit(1);
      }
    }
    Socket new_socket = Socket(new_fd);
    new_socket.SetNonBlock();
    Connection* new_connection = new Connection(new_socket);
    connections_[new_fd] = new_connection;
    new_connection->SetCallback
      ( std::bind(&TcpServer::Recver, this, new_connection)
      , std::bind(&TcpServer::Sender, this, new_connection)
      , nullptr);

    epoll_.SetEvent(new_socket, EPOLLIN | EPOLLET);
    LOG(log::LogLevel::kInfo, "add new connection over");
  }
}

void TcpServer::Recver(Connection* connection)
{
  LOG(log::LogLevel::kDebug, "tcp server recv");
  RemoveOverTimeConnection();
  while (true) {
    char buffer[kBufferNum];
    ssize_t sz  = recv(connection->GetFd(), buffer, sizeof(buffer) - 1, 0);
    if (sz < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        break;
      } else if (errno == EINTR) {
        continue;
      } else {
        // TODO : 可以给专门的错误码
        exit(1);
      }
    }
    else if (sz == 0) {
      LOG(log::LogLevel::kDebug, "tcp server close connect");
      break;
    }
    connection->read_buffer_member_variable() += buffer;
  }

  // 对端关闭连接
  if (connection->read_buffer_member_variable().empty()) {
    delete connection;
    return;
  }

  LOG(log::LogLevel::kDebug, connection->read_buffer_member_variable().c_str());
}

void TcpServer::Sender(Connection* connection)
{
  LOG(log::LogLevel::kDebug, "tcp server send");
  while (true) {
    ssize_t sz = send(connection->GetFd()
      , connection->write_buffer_member_variable().c_str()
      , connection->write_buffer_member_variable().size(), 0);
    if (sz == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        break;
      } else if (errno == EINTR) {
        continue;
      } else {
        // TODO : 可以给专门的错误码
        exit(1);
      }
    } else if (sz == 0) {
      break;
    }

    connection->write_buffer_member_variable().erase(0, sz);
  }
  connection->write_buffer_member_variable().clear();
  LOG(log::kDebug, "tcp server send end");
}

void TcpServer::RemoveOverTimeConnection()
{
  std::vector<int> over_time_connection = timer_.GetOverTimeKey();
  for (auto key : over_time_connection) {
    delete connections_[key];
    connections_.erase(key);
  }
}

} // namespace net
} // namespace web
