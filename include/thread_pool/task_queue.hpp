#pragma once
#include <queue>
#include <mutex>
#include <optional>
#include <condition_variable>
#include "task.hpp"

namespace threads {
class TaskQueue {
public:
    void Push(Task&& task);
    std::optional<Task> Pop();
    void Close();

private:
    std::mutex mutex_;
    std::condition_variable not_empty_;
    bool closed_ = false;
    std::queue<Task> queue_;
};
}  // namespace threads
