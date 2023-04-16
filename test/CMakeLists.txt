##########################################
## tests ##
##########################################

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
# add gtest
CPMAddPackage("gh:google/googletest#release-1.11.0")
# for gtest_discover_tests
include(GoogleTest)


# macro and tests
macro(add_boost_lib_test LIBNAME)
    add_executable(${LIBNAME} ${LIBNAME}.cpp)
    target_link_libraries(${LIBNAME} PRIVATE gtest gtest_main Boost::${LIBNAME})
    gtest_discover_tests(${LIBNAME})
endmacro()

# actual tests #
add_boost_lib_test(asio)
add_boost_lib_test(headers)
