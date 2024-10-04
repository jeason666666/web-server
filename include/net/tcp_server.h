#ifndef WEB_NET_TCP_SERVER_H
#define WEB_NET_TCP_SERVER_H

#include <functional>
#include <map>
#include <string>

#include "net/epoll.h"
#include "net/socket.h"

namespace web {
namespace net {

class Connection {
  using BindCallback = std::function<void()>;
  using Callback = std::function<void(Connection*)>;
public:
  Connection(const Socket& socket);

  void SetCallback
    ( BindCallback read_cb = nullptr, 
      BindCallback write_cb = nullptr, 
      BindCallback except_cb = nullptr);

  inline void Read() { read_cb_(); }
  inline void Write() { write_cb_(); }
  inline void Except() { except_cb_(); }

  inline int GetFd() { return socket_.fd_member_varible(); }

  inline Socket& socket_member_variable() { return socket_; }

  inline std::string& read_buffer_member_variable() 
    { return read_buffer_; }
  inline std::string& write_buffer_member_variable()
    { return write_buffer_; }

private:
  Socket socket_;
  BindCallback read_cb_;
  BindCallback write_cb_;
  BindCallback except_cb_;

  std::string read_buffer_;
  std::string write_buffer_;
};

const static char* kIp = "0.0.0.0";
const static uint16_t kPort = 443;

class TcpServer {
public:
  TcpServer();
  ~TcpServer();

  void Start();

  void LoopOnce();

  void Accepter(Connection* connection);

  virtual void Recver(Connection* connection);

  virtual void Sender(Connection* connection);

private:
  Epoll epoll_;
  Socket listen_socket_;
  std::unordered_map<int, Connection*> connections_;
  
};

} // namespace net
} // namespace web

#endif // WEB_NET_TCP_SERVER_H
