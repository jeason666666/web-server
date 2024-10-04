#include "task/thread_pool.h"

namespace web {
namespace task {

ThreadPool::ThreadPool(int thread_num)
{
  for (int i = 0; i < thread_num; i ++) {
    threads_.emplace_back(std::thread([this](){
      Task task;
      while (true) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return !tasks_.empty() || stop_; });
        if (stop_ && tasks_.empty()) {
          return;
        }
        task = std::move(tasks_.front());
        tasks_.pop();

        task();
      }
    }));
  }
}

ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(mtx_);
    stop_ = true;
  }

  cv_.notify_all();
  
  for (auto& thread : threads_) {
    thread.join();
  }
}

void ThreadPool::AddTask(Task task)
{
  {
    std::unique_lock<std::mutex> lock(mtx_);
    tasks_.push(task);
  }
  cv_.notify_one();
}

} // namespace task
} // namespace web
