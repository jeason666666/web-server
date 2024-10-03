#include "net/http.h"
#include <iostream>

namespace web_internal {
namespace net {

static const char kCR = '\r';
static const char kLF = '\n';
static const char kSpace = ' ';
static const char* kHeaderSEP = ": ";
static const char* kCRLF = "\r\n";

std::string get_status_message(int status)
{
  if      (status == 200) return "OK";
  else if (status == 404) return "NOT FOUND";
  // TODO : 不应该走到这里
  return nullptr;
}

Request::Request(const std::string& raw_str)
  : method_("GET")
  , path_("/")
  , version_("HTTP/1.1")
  , body_("")
{
  Serialize(raw_str);
}

void Request::Serialize(const std::string& raw_str)
{
  int last_field_pos = 0;
  int current_field_pos = 0;
  // 状态行
  // TODO : 错误处理
  current_field_pos = raw_str.find(kSpace, last_field_pos);
  method_ = raw_str.substr(0, current_field_pos - last_field_pos);
  last_field_pos = current_field_pos + 1;

  current_field_pos = raw_str.find(kSpace, last_field_pos);
  path_ = raw_str.substr(last_field_pos, current_field_pos - last_field_pos);
  last_field_pos = current_field_pos + 1;

  // TODO : 了解一下string的构造？
  current_field_pos = raw_str.find(kCRLF, last_field_pos);
  version_ = raw_str.substr(last_field_pos, current_field_pos - last_field_pos);
  last_field_pos = current_field_pos + 1;

  // 消息报头
  while (true) {
    current_field_pos = raw_str.find(kHeaderSEP, last_field_pos);
    if (current_field_pos == std::string::npos) {
      break;
    }
    std::string key(raw_str.substr(last_field_pos, current_field_pos - last_field_pos));
    last_field_pos = current_field_pos + 1;

    current_field_pos = raw_str.find(kCRLF, last_field_pos);
    std::string value(raw_str.substr(last_field_pos, current_field_pos - last_field_pos));
    last_field_pos = current_field_pos + 1;

    headers_[key] = value;
  }

  // 空行
  current_field_pos = raw_str.find(kCRLF, last_field_pos);
  last_field_pos = current_field_pos + 1;

  // 响应正文
  body_ = raw_str.substr(last_field_pos);
}


Response::Response()
  : version_("HTTP/1.1")
  , status_(200)
  , status_message_("OK")
{

}

void Response::SetHeader(const std::string& key, const std::string& value)
{
  headers_[key] = value;
}

void Response::SetBody(const std::string& body)
{
  body_ = body;
}

std::string Response::Deserialize()
{
  std::string resq;
  
  // 状态行
  resq += version_;
  resq += kSpace;

  resq += std::to_string(status_);
  resq += kSpace;

  resq += status_message_;
  resq += kCRLF;

  // 消息报头
  for (auto& [key, value] : headers_) {
    resq += key;
    resq += kHeaderSEP;
    resq += value;
    resq += kCRLF;
  }

  // 空行
  resq += kCRLF;

  // 响应正文
  resq += body_;

  return resq;
}

} // namespace net
} // namespace web_internal
