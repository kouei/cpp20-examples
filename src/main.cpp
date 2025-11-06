#include "coro.hpp"
#include <iostream>

int main() {
  // start coroutine:
  auto coroTask = coro(3); // initialize coroutine
  std::cout << "coro() started\n";

  // loop to resume the coroutine until it is done:
  while (coroTask.resume()) { // RESUME
    std::cout << "coro() suspended\n";
  }

  std::cout << "coro() done\n";
}
