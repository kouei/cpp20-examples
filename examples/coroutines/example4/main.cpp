#include "corotask.hpp" // for CoroTask
#include <iostream>

CoroTask coro() {
  std::cout << "    coro(): PART1\n";
  co_await std::suspend_always{}; // SUSPEND
  std::cout << "    coro(): PART2\n";
}

CoroTask callCoro() {
  std::cout << "  callCoro(): CALL coro()\n";
  auto sub = coro();     // init sub coroutine
  while (sub.resume()) { // RESUME sub coroutine
    std::cout << "  callCoro(): coro() suspended\n";
  }
  std::cout << "  callCoro(): coro() done\n";
  co_await std::suspend_always{}; // SUSPEND
  std::cout << "  callCoro(): END\n";
}

int main() {
  auto coroTask = callCoro(); // initialize coroutine
  std::cout << "MAIN: callCoro() initialized\n";

  while (coroTask.resume()) { // RESUME
    std::cout << "MAIN: callCoro() suspended\n";
  }

  std::cout << "MAIN: callCoro() done\n";
}
