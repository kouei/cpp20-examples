#include <iostream>
#include <list>
#include <vector>

template <typename T> class MyType {
private:
  T value;

public:
  MyType(const T &val) : value(val) {}

  void print() const { std::cout << value << "\n"; }

  bool isZero() const
    requires std::integral<T> || std::floating_point<T>
  {
    return value == 0;
  }
};

int main() {
  auto mt1 = MyType<double>{3.14};

  mt1.print();        // OK
  if (mt1.isZero()) { // OK
    std::cout << "mt1 is zero" << "\n";
  }

  auto mt2 = MyType<std::string>{"abc"};

  mt2.print(); // OK
  // if(mt2.isZero()) // Error

  return 0;
}