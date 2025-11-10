#include "resulttask.hpp" // for ResultTask
#include <coroutine>      // for std::suspend_always{}
#include <iostream>
#include <ranges>
#include <vector>

ResultTask<double> average(auto coll) {
  double sum = 0;
  for (const auto &elem : coll) {
    std::cout << "  process " << elem << '\n';
    sum = sum + elem;
    co_await std::suspend_always{}; // SUSPEND
  }
  co_return sum / std::ranges::ssize(coll); // return resulting average
}

int main() {
  std::vector values{0, 8, 15, 47, 11, 42};

  // start coroutine:
  auto task = average(std::views::all(values));

  // loop to resume the coroutine until all values have been processed:
  std::cout << "resume()\n";
  while (task.resume()) { // RESUME
    std::cout << "resume() again\n";
  }

  // print return value of coroutine:
  std::cout << "result: " << task.getResult() << '\n';
}
