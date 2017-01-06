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
//stxxl
#include <iostream>
//#ifdef _STXXL_PRINT_FLAGS_DEFAULT
//#undef _STXXL_PRINT_FLAGS_DEFAULT
//#define _STXXL_PRINT_FLAGS_DEFAULT  _STXXL_PRNT_LOG

//#endif

#define  _STXXL_VERBOSE_LEVEL -100
#include <stxxl/vector>
int main()
{
  typedef stxxl::VECTOR_GENERATOR<int>::result vector;
  vector my_vector;
  for (int i = 0; i < 1024 * 1024; i++)
  {
    my_vector.push_back(i + 2);
  }
  std::cout << my_vector[99] << std::endl;
  my_vector[100] = 0;
  while (!my_vector.empty())
  {
    my_vector.pop_back();
  }
  std::cout << _STXXL_VERBOSE_LEVEL << std::endl;
  return 0;
}