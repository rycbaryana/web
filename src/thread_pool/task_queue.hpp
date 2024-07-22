#pragma once
#include <queue>
#include <mutex>
#include <optional>
#include <condition_variable>
#include "../unique_function.hpp"

using Task = UniqueFunction<void()>;

class TaskQueue {
public:
    void Push(Task&& task) {
        if (closed_) {
            return;
        }
        std::lock_guard guard(mutex_);
        queue_.emplace(std::move(task));
        not_empty_.notify_one();
    }
    std::optional<Task> Pop() {
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
    void Close() {
        std::lock_guard guard(mutex_);
        closed_ = true;
        not_empty_.notify_all();
    }

private:
    std::mutex mutex_;
    std::condition_variable not_empty_;
    bool closed_ = false;
    std::queue<Task> queue_;
};