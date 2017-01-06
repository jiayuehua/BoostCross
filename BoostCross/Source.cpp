//#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <future>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <utility>
#include <atomic>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include "../../openSrc/fox/thread.hpp"
#include "../../openSrc/fox/mutex.hpp"
#include "../../openSrc/fox/scopedLock.hpp"
#include <tuple>
#include <unordered_map>
#include <memory>

//int main()
//{
//  std::cout << "hello, world!\n";
//}
//#include <iostream>
//#include <boost/filesystem.hpp>
//using namespace boost::filesystem;
//
//int main(int argc, char* argv[])
//{
//  if (argc < 2)
//  {
//    std::cout << "Usage: tut1 path\n";
//    return 1;
//  }
//  std::cout << argv[1] << " " << file_size(argv[1]) << '\n';
//  return 0;
//}
class A {
public:
  void foo(std::reference_wrapper<int> rw)
  {
    rw_ = rw;
    ++rw_;
  }
  std::reference_wrapper<int> rw_;
  A(std::reference_wrapper<int> rw) :rw_(rw) {
  }
};
bool isEven(int i)
{
  return !(i % 2);
}
void ForLoop(int n)
{
  for (int i = 0; i < n; ++i)
  {
    sleep(1);
    std::cout << "hello,world\n";
  }
}

void FutureFunc()
{
  auto fut = std::async(isEven, 20);
  auto fut1 = std::async(isEven, 91);
  auto fut2 = std::async(isEven, 81);
  auto fut3 = std::async(isEven, 71);
  auto fut4 = std::async(std::launch::async, ForLoop, 3);
  auto status = fut4.wait_for(std::chrono::seconds(1));
  if (status == std::future_status::ready)
  {
    std::cout << "ready\n";

  }
  else if (status == std::future_status::timeout)
  {
    std::cout << "timeout\n";  //timeout
  }
  else if (status == std::future_status::deferred)
  {
    std::cout << "deferred\n";
  }
  {
    auto fut4 = std::async(std::launch::async, ForLoop, 1);
    //auto status = fut4.wait_for(std::chrono::seconds(1));
    auto status = fut4.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(30));
    if (status == std::future_status::ready)
    {
      std::cout << "ready\n";//ready

    }
    else if (status == std::future_status::timeout)
    {
      std::cout << "timeout\n";
    }
    else if (status == std::future_status::deferred)
    {
      std::cout << "deferred\n";
    }
  }
  {
    auto fut4 = std::async(std::launch::deferred, ForLoop, 1);
    auto status = fut4.wait_for(std::chrono::seconds(4));
    if (status == std::future_status::ready)
    {
      std::cout << "ready\n";
    }
    else if (status == std::future_status::timeout)
    {
      std::cout << "timeout\n";
    }
    else if (status == std::future_status::deferred)
    {
      std::cout << "deferred\n"; //deferred
    }
  }
  fut4.get();

  std::cout << fut.get() << std::endl;
  std::cout << fut1.get() << std::endl;
  std::cout << fut2.get() << std::endl;
  std::cout << fut3.get() << std::endl;
}
std::mutex g_mutex;
int g = 0;
template <class T>
using TM = std::chrono::time_point<std::chrono::system_clock, T>;
void Chrono()
{
  //chro
  //std::chrono::seconds s(50);
  //std::chrono::milliseconds n = s;
  //std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes> (s);
  //std::cout << n.count() << std::endl;
  //std::cout << m.count() << std::endl;
  //std::chrono::minutes m(189);
  //s *= 189;
  //std::cout << "s is " << std::chrono::duration_cast<std::chrono::hours>(s).count()
  //  << ", " << (s % std::chrono::hours(1)).count() << std::endl;
  //std::cout << s.count()<<std::endl;
  //std::cout << "\n" << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch() ).count()<< std::endl;
  //std::cout << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch());
  std::cout << h.count() << std::endl;
  using days = std::chrono::duration<int64_t, std::ratio<24 * 3600L>>;
  TM<days> t = std::chrono::time_point_cast<days>(std::chrono::system_clock::now());
  //TM<std::chrono::years> y = std::chrono::time_point_cast<std::chrono::years>(std::chrono::system_clock::now());
  TM<std::chrono::minutes> m(t);
  TM<std::chrono::hours> th1 = std::chrono::time_point_cast<std::chrono::hours>(m);
  std::cout << t.time_since_epoch().count() << std::endl;
  std::cout << th1.time_since_epoch().count() << std::endl;
  //std::cout << m.time_since_epoch().count() << std::endl;
}

void Foo()
{
  //std::lock_guard<std::mutex> l(g_mutex);
  for (int i = 0; i < 500; ++i)
  {
    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    //std::lock_guard<std::mutex> l(g_mutex);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
    //std::cout << "i: " << i << "\n";
    ++g;
  }
  //for (int j = 0; j<100; ++j)
  //{
  //  std::cout << "j: " << j << "\n";
  //  ++g;
  //}
}


//void ThreadTestJoin()
//{
  //std::thread t1(Foo);
  //std::thread t2(Foo);
  //std::thread tb(Foo);
  //std::thread ta(Foo);
  //std::thread tc(Foo);
  //t1.join();
  //t2.join();
  //ta.join();
  //tb.join();
  //tc.join();
  //std::cout << g << std::endl;
//}
void ThreadTestID()
{
  std::lock_guard <std::mutex> l(g_mutex);
  std::cout << "ThreadTestId" << std::this_thread::get_id() << std::endl;
}
void ThreadTest()
{
  std::thread t1(ThreadTestID);
  t1.join();
  //std::thread t2(ThreadTestID);
  fox::Thread t3(ThreadTestID);
  fox::Thread t4;
  {

    std::lock_guard<std::mutex> l(g_mutex);

    std::cout << "t3: " << t3.get_id() << std::endl;
    std::cout << "t4: " << t4.get_id() << std::endl;
  }
  t4 = std::move(t3);
  {
    std::lock_guard<std::mutex> l(g_mutex);
    std::cout << "t3: " << t3.get_id() << std::endl;
    std::cout << "t4: " << t4.get_id() << std::endl;
  }
  //t1.join();
  //t2.join();
}

void RefWrap()
{
  int t = 1, b = 19;
  A a(t);
  A d(a);
  //a.foo(t);
  ++d.rw_;
  ++d.rw_;
  ++d.rw_;
  ++d.rw_;
  std::cout << b << std::endl;
  std::cout << t << std::endl;
  a.foo(b);
  std::cout << b << std::endl;
  std::cout << t << std::endl;
}

class Account {
public:
  int money_;
  std::mutex m;
};
void TransferMoney(Account & a, Account& b, int val)
{
  std::lock(a.m, b.m);
  std::lock_guard<std::mutex> la(a.m, std::adopt_lock);
  std::lock_guard<std::mutex> lb(a.m, std::adopt_lock);
  b.money_ += val;
  a.money_ -= val;
}
void MoneyLock()
{
  Account a;
  a.money_ = 10098;
  Account b;
  b.money_ = 109238;
  fox::Thread t(TransferMoney, std::ref(a), std::ref(b), 100);
  fox::Thread ta(TransferMoney, std::ref(b), std::ref(a), 334);
  fox::Thread tb(TransferMoney, std::ref(a), std::ref(b), 100);
  std::cout << a.money_ << std::endl;
  std::cout << b.money_ << std::endl;
}
//std::atomic<int> a(0);
int a(0);


struct OnceFlag {
  std::mutex m_;
  bool hascalled_ = false;
};

template< class Callable, class... Args >
void callOnce(OnceFlag& flag, Callable&& f, Args&&... args)
{
  std::lock_guard<std::mutex> l(flag.m_);
  if (!flag.hascalled_)
  {
    flag.hascalled_ = true;
    f(args...);
  }
}
OnceFlag onceflag;

void ThreadFooImpl()
{
  std::cout << "ThreadFooImpl\n";
  /*for (int i = 0; i<20000; ++i)
  {
    std::unique_lock<std::mutex> ul(g_mutex);
    ++a;
  }*/
}
std::recursive_mutex gRurMutex;
#include <iostream>
struct Human {
  int money;
  std::mutex m;
};
void transfer(Human& l, Human&r, int count)
{
  //std::lock_guard<std::mutex,std::mutex> lg(l.m, r.m);
  //std::scoped_lock(l.m, r.m);
  //std::scoped_lock(l.m);
  l.money -= count;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  r.money += count;
}
void ThreadFoo()
{
  fox::ScopedLock s(g_mutex);
  for (int i = 0; i < 5; ++i)
  {
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  //g_mutex.lock();
  //g_mutex.lock();
  //std::unique_lock<std::mutex>  lm(g_mutex);
  //lm.lock();
  //lm.unlock();
  //std::unique_lock<std::mutex>  lm2(g_mutex);
  //std::unique_lock<std::recursive_mutex> ul(gRurMutex);
  //std::cout << std::this_thread::get_id()<<"hello,world\n";
  //ul.lock();
  //ul.unlock();
}
void UniqueLockFoo()
{
  Human you{ 300 }, i{ 2345 };

  fox::Thread t(transfer, std::ref(you), std::ref(i), 1000);
  fox::Thread ta(transfer, std::ref(you), std::ref(i), 200);
  std::cout << you.money << " " << i.money << std::endl;
}
void LogicalNotFoo()noexcept
{
  //fox::Mutex<> m;

  std::vector<int> v{
    1,1,1,0,
  };
  auto it = std::find_if(v.cbegin(), v.cend(), std::logical_not<int>());
  if (it != v.cend())
  {
    std::cout << *it << std::endl;
  }
  std::transform(v.cbegin(), v.cend(), v.begin(), std::negate<int>());
  std::for_each(v.cbegin(), v.cend(), [](int i) {
    std::cout << i << std::endl;
  });

}
class AType {
};
class B :public AType {

};
int main()
{
  fox::GeneralMutex<fox::Timed> g;
  std::unique_lock<fox::GeneralMutex<fox::Timed> > u;
  u.lock();
  std::cout << boost::is_base_and_derived<AType, B>::value << std::endl;
  //LogicalNotFoo();
  //UniqueLockFoo();
}
void MainImpl()
{
  //fox::Thread t2(ThreadFoo);
  //fox::Thread t3(ThreadFoo);
  //fox::Thread t4(ThreadFoo);
  //auto t2 = std::async(std::launch::async, ThreadFoo);
  //auto t3 = std::async(std::launch::async, ThreadFoo);
  //auto t4 = std::async(std::launch::async, ThreadFoo);
  //std::cout << a << std::endl;
  //auto t = std::make_tuple(1, "hello");
  //std::unordered_map<int, std::string> m;

  //m.insert(t);

  //std::cout << std::get<0>(t)<<std::endl;
  //MoneyLock();
  //ThreadTest();
  //Chrono();
  //RefWrap();
  //FutureFunc();
}

//Р§зг
