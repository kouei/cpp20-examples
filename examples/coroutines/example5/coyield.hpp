#include "corogen.hpp" // for CoroGen
#include <iostream>

CoroGen coro(int max) {
  std::cout << "         CORO " << max << " start\n";

  for (int val = 1; val <= max; ++val) {
    // print next value:
    std::cout << "         CORO " << val << '/' << max << '\n';

    // yield next value:
    co_yield val; // SUSPEND with value
  }

  std::cout << "         CORO " << max << " end\n";
}
