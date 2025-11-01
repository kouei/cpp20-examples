#include <iostream>
#include <list>
#include <vector>

constexpr bool isPrime(int val) {
  if (val <= 1)
    return false;

  for (int i = 2; i <= val / 2; ++i) {
    if (val % i == 0)
      return false;
  }

  return true;
}

template <auto Val>
  requires(isPrime(Val))
class C1 {};

template <auto Val>
concept IsPrime = Val > 0 && isPrime(Val);

template <auto Val>
  requires IsPrime<Val>
class C2 {};

int main() {
  // auto c1 = C1<6>(); // Error
  // auto c2 = C1<7>(); // OK

  // auto c1 = C2<6>(); // Error
  // auto c2 = C2<7>(); // OK
  return 0;
}