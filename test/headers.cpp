#include <iostream>
#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

// lexical cast as an example of an header only library
TEST(boost_lib_tests, lexical_cast)
{
  std::string s{"42"};
  auto i = boost::lexical_cast<int>(s);
  EXPECT_EQ(i, 42);
}
