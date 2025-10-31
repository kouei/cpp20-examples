#include <set>
#include <vector>

// This also works.
// Remember that concepts and requirements are just "compile-time boolean
// values".
void add(auto &coll, const auto &val) {
  if constexpr (requires { coll.push_back(val); }) {
    coll.push_back(val);
  } else {
    coll.insert(val);
  }
}

int main() {
  std::vector<int> coll1;
  std::set<int> coll2;

  add(coll1, 42);
  add(coll2, 42);
  return 0;
}