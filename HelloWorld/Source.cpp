#include <iostream>
#include <functional>
#include <iostream>
#include  "../../openSrc/fox/Thread.hpp"


class A {
public:
  void foo(std::reference_wrapper<int> rw)
  {
    rw_ = rw;
    ++rw_;
  }
  std::reference_wrapper<int> rw_;
  A(std::reference_wrapper<int> rw) :rw_(rw) { }
};
void foo()
{
  std::cout << "foo\n";
}
int main()
{
  foo();
  std::cout << "hello,world! \n";
}