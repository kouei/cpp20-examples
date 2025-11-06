#include <iostream>
#include "corotask.hpp"   // for CoroTask

CoroTask coro(int max)
{
  std::cout << "         CORO " << max << " start\n";

  for (int val = 1; val <= max; ++val) {
    // print next value:
    std::cout << "         CORO " << val << '/' << max << '\n';

    co_await std::suspend_always{};     // SUSPEND
  }

  std::cout << "         CORO " << max << " end\n";
}