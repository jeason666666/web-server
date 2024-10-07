#ifndef WEB_TIME_TIMER_H
#define WEB_TIME_TIMER_H

#include <map>
#include <vector>

namespace web {
namespace time {

class Timer {
public:
  Timer(long int time_out);

  void Add(int key);

  void Refresh();

  std::vector<int> GetOverTimeKey();

private:
  // 自定key值，时间戳
  std::map<int, long int> timer_;
  long int last_fresh_time_ = 0;
  long int time_out_ = 0;
};

} // namespace time
} // namespace web

#endif // WEB_TIME_TIMER_H
