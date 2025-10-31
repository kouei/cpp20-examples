#include <set>
#include <vector>

template <typename CollT>
concept HasPushBack =
    requires(CollT c, CollT::value_type v) { c.push_back(v); };

// As an alternative, use "auto" to rewrite this.
// So that we can omit the template<...> part
void add(HasPushBack auto &coll, const auto &val) { coll.push_back(val); }

void add(auto &coll, const auto &val) { coll.insert(val); }

int main() {
  std::vector<int> coll1;
  std::set<int> coll2;

  static_assert(HasPushBack<std::vector<int>>);
  static_assert(!HasPushBack<std::set<int>>);

  add(coll1, 42);
  add(coll2, 42);
  return 0;
}