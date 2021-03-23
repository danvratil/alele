#pragma once

#if defined(_GNUC_)
#include <coroutine>
namespace Alele::coro {
    using suspend_never = std::suspend_never;
    using suspend_always = std::suspend_always;
    template<typename T = void>
    using coroutine_handle = std::coroutine_handle<T>;
} // namespace Alele::coro
#elif defined(__clang__)
#include <experimental/coroutine>
namespace Alele::coro {
    using suspend_never = std::experimental::suspend_never;
    using suspend_always = std::experimental::suspend_always;
    template<typename T = void>
    using coroutine_handle = std::experimental::coroutine_handle<T>;
} // namespace Alele::coro
#else
#pragma error "Current compiler is not supported."
#endif

namespace Alele::coro {

template<typename Op>
class Operation {
public:
    bool await_ready() const noexcept {
        return false;
    }

    bool await_suspend(coroutine_handle<> awaitingCoro) {
        mAwaitingCoro = awaitingCoro;
        return static_cast<Op *>(this)->start();
    }

    auto await_resume() {
        return static_cast<Op *>(this)->get_result();
    }

private:
    coroutine_handle<> mAwaitingCoro;
};


} // namespace Alele::coro
