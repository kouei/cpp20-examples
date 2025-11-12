#include "tracingawaiter.hpp"
#include "tracingcoro.hpp"
#include <iostream>

TracingCoro coro(int max) {
  std::cout << "  START coro(" << max << ")\n";
  for (int i = 1; i <= max; ++i) {
    std::cout << "  CORO: " << i << '/' << max << '\n';
    co_await TracingAwaiter{}; // SUSPEND
    std::cout << "  CONTINUE coro(" << max << ")\n";
  }
  std::cout << "  END coro(" << max << ")\n";
}

int main() {
  // start coroutine:
  std::cout << "**** start coro()\n";
  auto coroTask = coro(3); // init coroutine
  std::cout << "**** coro() started\n";

  // loop to resume the coroutine until it is done:
  std::cout << "\n**** resume coro() in loop\n";
  while (coroTask.resume()) { // RESUME
    std::cout << "**** coro() suspended\n";
    //...
    std::cout << "\n**** resume coro() in loop\n";
  }

  std::cout << "\n**** coro() loop done\n";
}
