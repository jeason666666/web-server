#ifndef WEB_NET_HTTP_H
#define WEB_NET_HTTP_H

#include <map>
#include <string>

namespace web {
namespace net {

using Headers = std::map<std::string, std::string>;

std::string get_status_message(int status);

struct Request {
  explicit Request(const std::string& raw_str);
  
  void Serialize(const std::string& raw_str);

  std::string method_;
  std::string path_;
  std::string version_;
  Headers headers_;
  std::string body_;
};

struct Response {
  explicit Response();

  void SetHeader(const std::string& key, const std::string& value);
  void SetBody(const std::string& body);

  std::string Deserialize();

  std::string version_;
  int status_ = -1;
  std::string status_message_; 
  Headers headers_;
  std::string body_;
};

} // namespace net
} // namespace web

#endif // WEB_NET_HTTP_H
