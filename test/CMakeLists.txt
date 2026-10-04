cmake_minimum_required(VERSION 3.15...3.22)

# add gtest
CPMAddPackage("gh:google/googletest@1.18.0")
# for gtest_discover_tests
include(GoogleTest)


##########################################
## tests ##
##########################################

# macro, assuming tests are named like the library
macro(add_boost_lib_test LIBNAME)
    add_executable(${LIBNAME} ${LIBNAME}.cpp)
    target_link_libraries(${LIBNAME} PRIVATE gtest gtest_main Boost::${LIBNAME})
    gtest_discover_tests(${LIBNAME})
endmacro()

# actual tests #
add_boost_lib_test(asio)
add_boost_lib_test(headers)
