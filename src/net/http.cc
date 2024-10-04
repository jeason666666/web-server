#include "net/http.h"

#include "log/log.h"

namespace web {
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
  
  ASSERT(false);
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
  current_field_pos = raw_str.find(kSpace, last_field_pos);
  ASSERT(current_field_pos != std::string::npos);
  method_ = raw_str.substr(0, current_field_pos - last_field_pos);
  last_field_pos = current_field_pos + 1;

  current_field_pos = raw_str.find(kSpace, last_field_pos);
  ASSERT(current_field_pos != std::string::npos);
  path_ = raw_str.substr(last_field_pos, current_field_pos - last_field_pos);
  last_field_pos = current_field_pos + 1;

  current_field_pos = raw_str.find(kCRLF, last_field_pos);
  ASSERT(current_field_pos != std::string::npos);
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
    ASSERT(current_field_pos != std::string::npos);
    std::string value(raw_str.substr(last_field_pos, current_field_pos - last_field_pos));
    last_field_pos = current_field_pos + 1;

    headers_[key] = value;
  }

  // 空行
  current_field_pos = raw_str.find(kCRLF, last_field_pos);
  ASSERT(current_field_pos != std::string::npos);
  last_field_pos = current_field_pos + 1;

  // 响应正文
  body_ = raw_str.substr(last_field_pos);
}


Response::Response()
  : version_("HTTP/1.1")
  , status_(-1)
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
  ASSERT(!version_.empty());
  resq += version_;
  resq += kSpace;

  ASSERT(status_ != -1);
  resq += std::to_string(status_);
  resq += kSpace;

  ASSERT(!status_message_.empty());
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
} // namespace web
