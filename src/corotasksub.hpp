#include <coroutine>
#include <exception> // for terminate()

// coroutine interface to deal with a simple task
// - providing resume() to resume it
// - including resuming sub-coroutines if there is one
class [[nodiscard]] CoroTaskSub {
public:
  // initialize members for state and customization:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;

private:
  CoroHdl hdl; // native coroutine handle

public:
  struct promise_type {
    CoroHdl subHdl;

    promise_type() : subHdl(nullptr) {}

    auto get_return_object() {
      return CoroTaskSub{CoroHdl::from_promise(*this)};
    }
    auto initial_suspend() { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
    auto final_suspend() noexcept { return std::suspend_always{}; }
  };

  // special members (no copy or move):
  CoroTaskSub(auto h) : hdl{h} { // store coroutine handle in interface
  }

  CoroTaskSub(const CoroTaskSub &) = delete;
  CoroTaskSub &operator=(const CoroTaskSub &) = delete;

  void destroy() {
    if (this->hdl) {
      this->hdl.destroy(); // destroy coroutine handle
    }
    this->hdl = nullptr;
  }

  ~CoroTaskSub() { this->destroy(); }

  // API to resume the deepest (sub) coroutine not done yet
  // - returns whether there is still something to process
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false; // nothing (more) to process
    }
    // find deepest sub-coroutine not done yet:
    auto innerHdl = hdl;
    while (innerHdl.promise().subHdl && !innerHdl.promise().subHdl.done()) {
      innerHdl = innerHdl.promise().subHdl;
    }

    innerHdl.resume(); // RESUME
    return !hdl.done();
  }

  // Let co_await handle its operand as sub-coroutine:
  bool await_ready() { return false; } // do not skip suspension
  void await_suspend(auto awaitHdl) {
    awaitHdl.promise().subHdl = hdl; // store sub-coroutine and suspend
  }
  void await_resume() {}
};
