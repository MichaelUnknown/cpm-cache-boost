cmake_minimum_required(VERSION 3.14)
project(cpm-cache-boost
    VERSION 1.81.0
    LANGUAGES CXX
)

# options
option(CPMCACHEBOOST_BUILD_TESTS "Enable building the tests" OFF)


# CPM
include(cmake/CPM.cmake)
# boost
CPMAddPackage(
  NAME Boost
  GITHUB_REPOSITORY boostorg/boost
  GIT_TAG boost-1.81.0
  VERSION 1.81.0
)

# headers
if(NOT TARGET Boost::headers)
message(STATUS "manually adding Boost::headers")
set(__boost_libs_dir "${Boost_SOURCE_DIR}/libs/")
file(GLOB __boost_all_components
  LIST_DIRECTORIES true
  RELATIVE "${__boost_libs_dir}"
  "${__boost_libs_dir}/*/include")
file(GLOB __boost_all_components_num
  LIST_DIRECTORIES true
  RELATIVE "${__boost_libs_dir}"
  "${__boost_libs_dir}/numeric/*/include")
foreach(__dir ${__boost_all_components})
  set(__full_dir "${__boost_libs_dir}${__dir}")
  list(APPEND __boost_all_includes ${__full_dir})
endforeach()
foreach(__dir ${__boost_all_components_num})
  set(__full_dir "${__boost_libs_dir}${__dir}")
  list(APPEND __boost_all_includes ${__full_dir})
endforeach()
list(LENGTH __boost_all_includes __boost_all_includes_count)
message(STATUS "number of include dirs discovered: ${__boost_all_includes_count}")
# add target
add_library(Boost::headers INTERFACE IMPORTED)
set_target_properties(Boost::headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__boost_all_includes}")
endif()

# run tests if set
if(CPMCACHEBOOST_BUILD_TESTS)
    message(STATUS "cpm cache boost: testing enabled")
    enable_testing()
    add_subdirectory(test)
else()
    message(STATUS "cpm cache boost: testing DISABLED")
endif()
