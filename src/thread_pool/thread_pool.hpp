#pragma once
#include <vector>
#include <thread>
#include "task_queue.hpp"
class ThreadPool {
public:
    ThreadPool(size_t size) : size_(size) {
        for (int i = 0; i < size; ++i) {
            workers_.emplace_back([this] { Work(); });
        }
    }
    void Submit(Task&& task) {
        tasks_.Push(std::move(task));
    }
    size_t Size() {
        return size_;
    }
    ~ThreadPool() {
        tasks_.Close();
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    void Work() {
        while (auto task = tasks_.Pop()) {
            (*task)();
        }
    }

private:
    std::vector<std::thread> workers_;
    TaskQueue tasks_;
    size_t size_;
};