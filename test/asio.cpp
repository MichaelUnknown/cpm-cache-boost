#include <iostream>
#include <boost/asio.hpp>

#include <gtest/gtest.h>

TEST(boost_lib_tests, asio)
{
  boost::asio::io_context io;
  auto i = 42;
  boost::asio::steady_timer t(io, boost::asio::chrono::milliseconds(200));
  t.wait();
  EXPECT_EQ(i, 42);
}
