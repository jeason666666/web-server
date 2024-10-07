#include "net/http_server.h"

#include <iostream>

#include "log/log.h"


namespace web {
namespace net {

static const int kBufferNum = 1024;

void HttpServer::Recver(Connection* connection)
{
  TcpServer::Recver(connection);

  // 对端关闭连接
  if (connection->read_buffer_member_variable().empty()) {
    return;
  }

  Request req(connection->read_buffer_member_variable());  
  Response resp;
  // TODO : 错误处理
  if (req.method_ == "GET") {
    if (get_method_mp_.count(req.path_)) {
      resp.status_ = 200;

      ASSERT(get_method_mp_[req.path_] != nullptr);
      get_method_mp_[req.path_](req, resp);
    
    } else {
      resp.status_ = 404;
      // TODO : 用status获取message
    }
  } else if (req.method_ == "POST") {
    if (post_method_mp_.count(req.path_)) {
      resp.status_ = 200;

      ASSERT(post_method_mp_[req.path_] != nullptr);
      post_method_mp_[req.path_](req, resp);

    } else {
      resp.status_ = 404;
    }
  }
  resp.status_message_ = get_status_message(resp.status_);
  resp.SetHeader("Content-Length", std::to_string(resp.body_.length()));

  // TODO : 改成触发写事件
  connection->write_buffer_member_variable() += resp.Deserialize();
  connection->read_buffer_member_variable().clear();
  LOG(log::kDebug, connection->write_buffer_member_variable().c_str());
  
  Sender(connection);
}

void HttpServer::Sender(Connection* connection)
{
  TcpServer::Sender(connection);
}

void HttpServer::Get(const std::string& path, Handler&& handler)
{
  get_method_mp_[path] = handler;
}

void HttpServer::Post(const std::string& path, Handler&& handler)
{
  post_method_mp_[path] = handler;
}


} // namespace net
} // namespace web
