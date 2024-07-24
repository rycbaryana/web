#include <thread_pool/task_queue.hpp>
namespace threads {
void TaskQueue::Push(Task&& task) {
    if (closed_) {
        return;
    }
    std::lock_guard guard(mutex_);
    queue_.emplace(std::move(task));
    not_empty_.notify_one();
}
std::optional<Task> TaskQueue::Pop() {
    std::unique_lock lock(mutex_);
    while (!closed_ && queue_.empty()) {
        not_empty_.wait(lock);
    }
    if (!queue_.empty()) {
        auto front = std::move(queue_.front());
        queue_.pop();
        return std::move(front);
    } else {
        return std::nullopt;
    }
}
void TaskQueue::Close() {
    std::lock_guard guard(mutex_);
    closed_ = true;
    not_empty_.notify_all();
}
}  // namespace threads
