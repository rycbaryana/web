#pragma once
#include <vector>
#include <thread>
#include "task_queue.hpp"

namespace threads {
class ThreadPool {
public:
    ThreadPool(size_t size);
    void Submit(Task&& task);
    size_t Size() {
        return size_;
    }
    ~ThreadPool();

private:
    void Work();

private:
    std::vector<std::thread> workers_;
    TaskQueue tasks_;
    size_t size_;
};
}  // namespace threads
