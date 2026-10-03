cmake_minimum_required(VERSION 3.14)
project(cpm-cache-boost
    VERSION 1.92.0
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
  GIT_TAG boost-1.92.0
  VERSION 1.92.0
)

# add headers and boost (targets from boost lib are just dummies)
message(STATUS "cpm cache boost: adjusting Boost::headers")
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
message(STATUS "cpm cache boost: added ${__boost_all_includes_count} include directories")
# add target
if(NOT TARGET Boost::headers)
  add_library(Boost::headers INTERFACE IMPORTED)
  set_target_properties(Boost::headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__boost_all_includes}")
  add_library(Boost::boost ALIAS Boost::headers)
else()
  get_target_property(__boost_headers_alias Boost::headers ALIASED_TARGET)
  set_target_properties("${__boost_headers_alias}" PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__boost_all_includes}")
  if(NOT TARGET Boost::boost)
    add_library(Boost::boost ALIAS "${__boost_headers_alias}")
  endif()
endif()


# run tests if set
if(CPMCACHEBOOST_BUILD_TESTS)
    message(STATUS "cpm cache boost: testing enabled")
    enable_testing()
    add_subdirectory(test)
else()
    message(STATUS "cpm cache boost: testing DISABLED")
endif()
