#include <set>
#include <vector>

// Without this HasPushBack, the compiler will produces error about redefinition
// of add()
template <typename CollT>
concept HasPushBack =
    requires(CollT c, CollT::value_type v) { c.push_back(v); };

template <typename CollT, typename T>
  requires HasPushBack<CollT>
void add(CollT &coll, const T &val) {
  coll.push_back(val);
}

template <typename CollT, typename T> void add(CollT &coll, const T &val) {
  coll.insert(val);
}

int main() {
  std::vector<int> coll1;
  std::set<int> coll2;

  // Use static_assert to test whether a concept is satisfied or not.
  // We should treat these checks as UT.
  static_assert(HasPushBack<std::vector<int>>);
  static_assert(!HasPushBack<std::set<int>>);

  add(coll1, 42);
  add(coll2, 42);
  return 0;
}