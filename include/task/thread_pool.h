#ifndef WEB_TASK_THREAD_POOL_H
#define WEB_TASK_THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace web {
namespace task {

using Task = std::function<void()>;

class ThreadPool {
public:
  ThreadPool(int thread_num = std::thread::hardware_concurrency());
  ~ThreadPool();

  void AddTask(Task task);

private:
  std::mutex mtx_;
  std::vector<std::thread> threads_;
  std::condition_variable cv_;
  std::queue<Task> tasks_;
  bool stop_ = false;
};

} // namespace task
} // namespace web

#endif // WEB_TASK_THREAD_POOL_H
