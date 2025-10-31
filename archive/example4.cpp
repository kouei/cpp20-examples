#include <ranges>
#include <set>
#include <vector>

template <typename CollT>
concept HasPushBack =
    requires(CollT c, std::ranges::range_value_t<CollT> v) { c.push_back(v); };

// This works now.
void add(auto &coll, const auto &val)
  requires HasPushBack<decltype(coll)>
{
  coll.push_back(val);
}

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