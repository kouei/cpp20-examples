#include "coro.hpp"
#include <iostream>

int main() {
  // start two coroutines:
  auto coroTask1 = coro(3); // initialize 1st coroutine
  auto coroTask2 = coro(5); // initialize 2nd coroutine
  std::cout << "coro(3) and coro(5) started\n";

  coroTask2.resume(); // RESUME 2nd coroutine once

  // loop to resume the 1st coroutine until it is done:
  while (coroTask1.resume()) { // RESUME 1st coroutine
    std::cout << "coro() suspended\n";
  }

  std::cout << "coro() done\n";

  coroTask2.resume(); // RESUME 2nd coroutine again
}
