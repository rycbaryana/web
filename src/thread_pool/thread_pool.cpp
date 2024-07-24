#include <thread_pool/thread_pool.hpp>
namespace threads {

ThreadPool::ThreadPool(size_t size) : size_(size) {
    for (int i = 0; i < size; ++i) {
        workers_.emplace_back([this] { Work(); });
    }
}
void ThreadPool::Submit(Task&& task) {
    tasks_.Push(std::move(task));
}
ThreadPool::~ThreadPool() {
    tasks_.Close();
    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::Work() {
    while (auto task = tasks_.Pop()) {
        (*task)();
    }
}
};  // namespace threads