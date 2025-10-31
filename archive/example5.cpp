#include <cstdint>
#include <set>
#include <vector>

template <typename CollT, typename T>
concept CanPushBack = requires(CollT c, const T &v) { c.push_back(v); };

template <typename CollT, typename T>
  requires CanPushBack<CollT, T>
void add(CollT &coll, const T &val) {
  coll.push_back(val);
}

void add(auto &coll, const auto &val) { coll.insert(val); }

int main() {
  std::vector<int> coll1;
  std::set<int> coll2;

  // We should be able to push_back() uint8_t to std::vector<int>
  static_assert(CanPushBack<std::vector<int>, uint8_t>);

  add(coll1, 42);
  add(coll2, 42);
  return 0;
}