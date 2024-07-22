#pragma once
#include <memory>


template <typename T>
class UniqueFunction;

template <typename R, typename... Args>
class UniqueFunction<R(Args...)> {
    struct Callable {
        virtual R Call(Args...) = 0;
        virtual~Callable() = default;
    };
    template <typename F>
    struct CallableImpl : Callable {
        explicit CallableImpl(F&& f) : f(std::move(f)) {
        }
        R Call(Args... args) override {
            return f(std::forward<Args>(args)...);
        }
        F f;
    };
public:
    template <typename F>
    UniqueFunction(F&& f) : callback_(std::make_unique<CallableImpl<F>>(std::forward<F>(f))) {
    }

    // Movable
    UniqueFunction(UniqueFunction&&) = default;
    UniqueFunction& operator=(UniqueFunction&&) = default;
    // Non-copyable
    UniqueFunction(const UniqueFunction&) = delete;
    UniqueFunction& operator=(const UniqueFunction&) = delete;

    R operator()(Args... args) const {
        return callback_->Call(std::forward<Args>(args)...);
    }

private:
    std::unique_ptr<Callable> callback_;
};



