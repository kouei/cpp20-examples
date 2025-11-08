#include "coyield.hpp"
#include <iostream>
int main() {
  // start coroutine:
  auto coroGen = coro(3);
  std::cout << "coro() started\n";
  // loop to resume the coroutine until it is done:
  while (coroGen.resume()) {
    // initialize coroutine
    // RESUME
    auto val = coroGen.getValue();
    std::cout << "coro() suspended with " << val << '\n';
  }
  std::cout << "coro() done\n";
}