#include "time/timer.h"

#include <time.h>

namespace web {
namespace time {

Timer::Timer(long int time_out)
  : time_out_(time_out)
{
}

void Timer::Add(int key)
{
  Refresh();
  timer_[key] = 0;
}

void Timer::Refresh()
{
  long int cur_time = ::time(0);
  long int delta_time = cur_time - last_fresh_time_;
  last_fresh_time_ = cur_time;

  for (auto& [key, time] : timer_) {
    time += delta_time;
  }
}

std::vector<int> Timer::GetOverTimeKey()
{
  Refresh();
  std::vector<int> over_time_keys;

  for (auto& [key, time] : timer_) {
    if (time > time_out_) {
      over_time_keys.push_back(time);
    }
  }

  return over_time_keys;
}

} // namespace time
} // namespace web
