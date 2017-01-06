#include <experimental/string_view>
#include <utility>
#include <memory>
#include <iterator>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/endian/arithmetic.hpp>

#include <range/v3/all.hpp>
#include <map>
#include <list>
#include <iostream>
#include <functional>
#include <algorithm>
#include <deque>
#include <boost/range/algorithm.hpp>
#include <vector>
//#define StringView(a) std::string_view(a,sizeof(a)-1)
//range::copy

#include "unique_erase.h"
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
  boost::range::equal(c, e, std::greater<>());
  boost::range::sort(e, std::greater<>());
  boost::range::for_each(e, [](double i) {std::cout << i << " "; });
  std::cout << "\n";
  return;

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

  std::cout << std::equal(a.cbegin(), a.cend(), b.begin()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::equal_to<double>()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::not_equal_to<double>()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::less<double>()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::greater<double>()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::greater_equal<double>()) << std::endl;
  std::cout << std::equal(a.cbegin(), a.cend(), b.begin(), std::less_equal<double>()) << std::endl;
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
  for (int i : r)
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
  for (int i : vb)
  {
    std::cout << i << std::endl;
  }
}

void StringFoo()
{
  std::string a("hello, world");
  std::string b("good, world");
  std::cout << std::exchange(a, std::move(b)) << std::endl;
  std::cout << b << std::endl;
}

void autoExchange()
{
  std::auto_ptr<int> a(new int(100));
  std::auto_ptr<int> b(new int(99));
  std::cout << *std::exchange(a, b) << std::endl;
  std::cout << "a: " << *a << std::endl;
  std::cout << "b: " << b.get() << std::endl;
}
template<class T>
void outputRange(const T& t)
{
  boost::for_each(t, [](auto& i)
  {
    std::cout << i << ",";
  }
  );
  std::cout << std::endl;
};
void ForEachFoo()
{
  namespace myrange = boost::range;
  std::list<int> n{
    1,2,2,2,2,2,3,3,33,9,4
  };
  std::list<int> l{
    1,2,9,7,6,2,3,3,3,4,4,4,4,5,5,5,5,5,2,2
  };
  std::vector<int> v{
    1,0,0,2,2,7,3,3,3,4,4,4,4,5,5,5,5,5,2,2
  };

  std::vector<int> o{
    1,2,2,2,2,2,3,3,3,4,4,4,4,5,5,5,5,5,2,2
  };
  std::vector<int> b{
    2,2
  };
  {
    //auto j = myrange::partial_sort(v, v.begin() + 8);
    //outputRange(j);
    //j = myrange::nth_element(v, v.begin() + 8);
    //outputRange(j);
    //auto q = myrange::remove<boost::return_found_end>(v, 2);
    ////myrange::remove_erase()

    //outputRange(q);
    /*auto n = myrange::unique<boost::return_found_end>(v);
    outputRange(n);*/
    outputRange(v);
    auto vu = myrange::unique_erase(v);
    outputRange(vu);
    //outputRange(n);
    auto va = myrange::partition<boost::return_found_end>(v, [](auto t) {
      return t < 3;
    });
    //std::cout << *va;
    //outputRange(va);
    return;
  }
  {
    myrange::for_each(v, [](int & i) {
      if (i != 2)
      {
        i *= 2;
      }
    });
    std::cout << "for_each\n";
    outputRange(v);
  }
  {
    auto p = boost::mismatch(l, n);
    std::cout << "mismatch\n";
    std::cout << *p.first << "," << *p.second << std::endl;
  }
  {
    std::cout << "equal\n";
    std::cout << boost::equal(l, n) << std::endl;
  }
  {
    std::cout << "find\n";
    auto i = boost::find(l, 5);
    if (i != l.end())
    {
      std::cout << *i << std::endl;
    }
  }
  {
    std::cout << "find_if\n";
    auto i = boost::find_if(l, [](auto i) {return i == 3; });
    if (i != l.end())
    {
      std::cout << *i << std::endl;
    }
  }
  {
    std::cout << "rotate_copy\n";
    myrange::rotate_copy(v, v.begin() + 5, o.begin());
    outputRange(o);
  }

  {
    std::cout << "fill\n";
    myrange::fill(o, 0);
    outputRange(o);
    std::cout << "fill_n\n";
    auto t = myrange::fill_n(o, o.size() / 2, 100);
    outputRange(t);

    auto r = myrange::unique<boost::return_found_end>(o);
    auto ra = boost::erase(o, r);
    outputRange(o);



    //outputRange(boost::make_iterator_range(o.begin(), r));
    //std::cout << *r;
    //auto j = myrange::adjacent_find(o);
    //std::cout << *j;
    //auto ro = myrange::rotate(v, v.begin() + 2);


    //outputRange(ro);
  }
  {

  }
  {
    auto i = myrange::partition(v, [](int i) {
      return i < 3;
    });
    std::cout << "partition\n";
    outputRange(boost::make_iterator_range(v.begin(), i));
    outputRange(boost::make_iterator_range(i, v.end()));
  }
  {
    std::cout << "nth_element\n";
    auto t = myrange::nth_element(v, v.begin() + 5);
    outputRange(t);
    outputRange(boost::make_iterator_range(v.begin(), v.begin() + 5));
    outputRange(boost::make_iterator_range(v.begin() + 5, v.end()));
    myrange::nth_element(v, v.begin() + 5, std::greater<int>());
    outputRange(boost::make_iterator_range(v.begin(), v.begin() + 5));
    outputRange(boost::make_iterator_range(v.begin() + 5, v.end()));
  }
  {
    std::cout << "subRange\n";
    boost::sub_range<std::vector<int> > sr(v);
    outputRange(sr.advance_begin(5).advance_end(-2));
  }
  {
    std::cout << "remove_if\n";
    boost::sub_range<std::vector<int> > sr(v);
    myrange::remove_erase(v, 2);
    outputRange(v);
  }

  {
    std::cout << "map_values\n";
    std::map<int, int>  sr{ { 1,2 },{ 3,4 } };
    auto t = myrange::find(sr | boost::adaptors::map_values, 4);
    std::cout << *t;
    //outputRange(v);
  }

  return;

  auto itv = boost::search_n(v, 5, 2);


  if (itv != v.end())
  {
    std::cout << *itv << std::endl;
  }
  auto it = boost::find_first_of(v, b);
  if (it != v.end())
  {
    std::cout << *it << std::endl;
  }
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

  {

    auto it = boost::search(v, b);

    boost::for_each(std::make_pair(it, v.end()), [](int i) {
      std::cout << i << " ";
    });
    std::cout << std::endl;
    it = boost::find_end(v, b);

    boost::for_each(std::make_pair(it, v.end()), [](int i) {
      std::cout << i << " ";
    });
    std::cout << std::endl;
  }


}
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
    1,2,8,9,7,5,5,5,6
  };
  std::vector<int> v{
    2,3,4
  };
  auto k = v | ranges::v3::view::remove_if([](int i) {
    return i == 5;
  });
  ranges::v3::copy(k, l.begin());
  ranges::v3::copy(v | ranges::v3::view::remove_if([](int i) {
    return i == 5;
  }), l.begin());

  auto n = ranges::v3::search_n(v | ranges::v3::view::take(8), 2, 5);
  if (n.get_unsafe() != v.end())
  {
    std::cout << *n.get_unsafe() << " ,";
  }


  //std::cout << *k<<" ,";
  // k = ranges::v3::search_n(l|ranges::v3:take(8), 2, 9);
  //std::cout << *k<<" ,";

  auto i = ranges::v3::adjacent_find(l, [](int l, int r) {
    return l > r;
  });
  auto j = ranges::v3::is_sorted_until(l);
  std::cout << *i << " " << *j;
  std::cout << std::endl;

  ranges::v3::copy(v, l.begin());
  ranges::v3::copy_if(l, v.end(), [](int i) {
    return i % 2 == 0;
  });
  //std::swap_ranges(l.begin(), l.end(), v.begin());
  ranges::v3::swap_ranges(l, v);

  boost::for_each(l, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
  boost::for_each(v, [](int i) {
    std::cout << i << " ";
  });
  std::cout << std::endl;
}


//void AnyFn(std::vector<int> &v)
//{
//
//  std::cout << ranges::any_of(v, [](int i) {
//    return i % 9 == 0;
//  });
//  std::cout << std::all_of(v.begin(), v.end(), [](int i) {
//    return i % 10 == 9;
//  });
//  std::cout << std::any_of(v.begin(), v.end(), [](int i) {
//    return i % 2 == 0;
//  });
//}

//void AnyofFoo()
//{
//  std::vector<int> v{
//    1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,2,2,1
//  };
//  std::vector<int> b{
//    2,2
//  };
//
//  std::cout<<ranges::v3::size(b)<<std::endl;
//  ranges::v3::size(b | ranges::view::remove_if([](int i) {
//    return i == 2;
//  }));
//  ranges::for_each(v | ranges::view::take(5), [](int i) {
//    std::cout << i << " ";
//  });
//  return;
//}
//using namespace boost::endian;
//union Myunion
//{
//  char c[4];
//  big_int32_t b;
//  int32_t l;
//};
//void fooEndian()
//{
//  Myunion m;
//  std::iota(m.c, m.c + 4, 0);
//  std::cout << m.b << std::endl;
//  std::cout << m.l << std::endl;
//}

int main()
{
  //fooEndian();
  //SwapRanges();
  //AnyofFoo();
  ForEachFoo();
  //StringFoo();
  //autoExchange();
  //fooTransform();
}