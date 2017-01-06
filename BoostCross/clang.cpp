//#include <iostream>
//#include <string_view>
//#define StringView(a) std::string_view(a,sizeof(a)-1)
#include <experimental/string_view>
#include <utility>
#include <memory>
#include <iterator>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <range/v3/all.hpp>
//range::copy


#define _SV(a) a,sizeof(a)-1
//void Stringview()
//{
//  std::string_view V2(_SV("hello,world"));
//  std::cout << V2 << std::endl;
//  std::string_view v("dbcadlcbabdca");
//  std::cout << v.size()  << std::endl;
//  std::string_view sv = StringView("hello,world");
//  std::cout << sv.size() << std::endl;
//  std::cout << (v == sv) << std::endl;
//  std::size_t lBegin = v.find('l', 0);
//  std::cout << v.substr(lBegin, 3)<<std::endl;
//  lBegin = v.find_first_of("abcd", 4, 2);
//  std::cout<< v.substr(lBegin) ;
//  v.remove_prefix(5);
//  std::cout << v << std::endl;
//  v.remove_suffix(2);
//  std::cout << v << std::endl;
//}
//int main()
//{
//  Stringview();
//}
#include <iostream>
#include <functional>
#include <algorithm>
#include <deque>
#include <boost/range/algorithm.hpp>
#include <vector>
void foo()
{
  std::vector<double> a{
    1,2,3,4,5
  };
  std::vector<double> b{
    4,5,6,7,8
  };
  std::vector<double> d{
    4,5,6,8,9
  };
  std::vector<double> c{
    4,7,7,8,9
  };
  std::vector<double> e{
    1,3,2,8,9,3,8
  };
  //boost::range::sort(e, std::greater<>());
  //boost::range::for_each(e, [](double i) {std::cout << i << " "; });
  //std::cout << "\n";
  boost::range::equal(c,e, std::greater<>());
  boost::range::sort(e, std::greater<>());
  boost::range::for_each(e, [](double i) {std::cout << i << " "; });
  std::cout << "\n";
  return ;

  std::vector<double> r(5);
  boost::range::reverse(c);
  boost::range::reverse(d);
  //boost::range::merge(a, b, r.begin());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";
  std::vector<double> rz(c.size() + d.size());

  boost::range::merge(c, d, rz.begin(), std::greater<double>());

  boost::range::for_each(rz, [](double i) {
    std::cout << i << " ";
  });

  std::cout << "\n";
  std::transform(a.cbegin(), a.cend(), b.cbegin(), r.begin(), std::plus<double>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";

  std::transform(a.cbegin(), a.cend(), b.cbegin(), r.begin(), std::minus<double>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";

  std::transform(a.cbegin(), a.cend(), b.cbegin(), r.begin(), std::multiplies<double>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";

  std::transform(a.cbegin(), a.cend(), b.cbegin(), r.begin(), std::modulus<int>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";
  std::transform(a.cbegin(), a.cend(), b.cbegin(), r.begin(), std::divides<double>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";
  std::transform(a.cbegin(), a.cend(), r.begin(), std::negate<double>());
  boost::range::for_each(r, [](double i) {
    std::cout << i << " ";
  });
  std::cout << "\n";

  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::equal_to<double>())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::not_equal_to<double>())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::less<double>())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::greater<double>())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::greater_equal<double>())<<std::endl;
  std::cout<<std::equal(a.cbegin(), a.cend(), b.begin(), std::less_equal<double>())<<std::endl;
}
struct Plus {
  template<class T>
  T operator()(const T& l, const T&r)const
  {
    return l + r;
  }
};
namespace boostRange = boost::range;
void fooTransform()
{
  std::vector<int> va{
    1,2,3,4,5
  };
  std::vector<int> vb{
    3,6,8,10,15
  };
  std::vector<int> r(vb.size());

  boostRange::transform(va, vb, r.begin(), std::plus<int>());
  for (int i: r)
  {
    std::cout << i << std::endl;
  }
}

void fooTransform2()
{
  std::vector<int> va{
    1,2,3,4,5
  };
  std::vector<int> vb{
    3,6,8,10,15
  };
  using namespace std::placeholders;
  boostRange::transform(va, vb.begin(), std::bind(Plus(), 7, _1));
  for (int i: vb)
  {
    std::cout << i << std::endl;
  }
}

void StringFoo()
{
  std::string a("hello, world");
  std::string b("good, world");
  std::cout<<std::exchange(a,std::move( b))<<std::endl;
  std::cout<< b<<std::endl;
}

void autoExchange()
{
  std::auto_ptr<int> a(new int(100));
  std::auto_ptr<int> b(new int(99));
  std::cout << *std::exchange(a, b) << std::endl;
  std::cout << "a: " << *a << std::endl;
  std::cout << "b: " << b.get() << std::endl;
}
void ForEachFoo()
{
  std::vector<int> v{
    1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,2,2
  };
  std::vector<int> b{
    2,2
  };
  std::vector<int> r;
  //boost::remove_copy(v, std::back_inserter(r), 4);
  //boost::replace_copy(v, std::back_inserter(r), 4, 9);

  boost::for_each(v, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
  boost::for_each(r, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;

  auto i = boost::remove(v, 4);
  v.erase(i, v.end());
  boost::for_each(v, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;

  auto it = boost::search(v, b);

  boost::for_each(std::make_pair(it,v.end()), [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
   it = boost::find_end(v, b);

  boost::for_each(std::make_pair(it,v.end()), [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
}
#include <list>
void Listfoo()
{
  std::list<int> l{ 1,9,7,4 };
  std::vector<std::reference_wrapper<int> > v(l.begin(), l.end());
  boost::sort(v);

  boost::for_each(l, [](int i) {
    std::cout << i << " ";
  });
}
void SwapRanges()
{
  std::list<int> l{
    1,2,8,9
  };
  std::vector<int> v{
    1,2,3,4
  };
  ranges::copy_if(l, v.end(), [](int i) {
    i % 2 == 0;
  });
  //std::swap_ranges(l.begin(), l.end(), v.begin());
  ranges::swap_ranges(l, v);

  boost::for_each(l, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
  boost::for_each(v, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
}


void AnyFn(std::vector<int> &v)
{

  std::cout << ranges::any_of(v, [](int i) {
    return i % 9 == 0;
  });
  std::cout << std::all_of(v.begin(), v.end(), [](int i) {
    return i % 10 == 9;
  });
  std::cout << std::any_of(v.begin(), v.end(), [](int i) {
    return i % 2 == 0;
  });
}

void AnyofFoo()
{
  std::vector<int> v{
    1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,2,2,1
  };
  std::vector<int> b{
    2,2
  };
  boost::push_back(v|)

  std::cout<<ranges::v3::size(b)<<std::endl;
  ranges::v3::size(b | ranges::view::remove_if([](int i) {
    return i == 2;
  }));
  ranges::for_each(v | ranges::view::take(5), [](int i) {
    std::cout << i << " ";
  });
  return;
}

int main()
{
  //SwapRanges();
  AnyofFoo();
  //ForEachFoo();
  //StringFoo();
  //autoExchange();
  //fooTransform();
}