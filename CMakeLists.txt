cmake_minimum_required(VERSION 3.15...3.22)
project(
  cpm-cache-boost
  VERSION 1.92.0
  LANGUAGES CXX
)

# options
option(CPMCACHEBOOST_BUILD_TESTS "Enable building the tests" OFF)
option(CPMCACHEBOOST_DEBUG_SHOW_INC_DIRS "Shows debug info / include directories" OFF)
# CPM
include(cmake/CPM.cmake)
# actual boost lib, use tar.xz for small file size (~100mb)
CPMAddPackage(
  NAME Boost
  VERSION 1.92.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.92.0/boost-1.92.0-cmake.tar.xz
  URL_HASH SHA256=9bed76128d4e46755dbe818487788c6fceb6f72b378f4daa49b7e1e600d9088d
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_SKIP_INSTALL_RULES ON" # Set `OFF` for installation
          "BUILD_SHARED_LIBS OFF"
)


# optional debug info
if(CPMCACHEBOOST_DEBUG_SHOW_INC_DIRS AND TARGET Boost::headers)
  message(STATUS "cpm cache boost: before adjusting")
  get_target_property(__boost_test_includes Boost::headers INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "cpm cache boost: Boost::headers includes are: ${__boost_test_includes}")
endif()

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
  if(NOT TARGET Boost::boost)
    add_library(Boost::boost ALIAS Boost::headers)
  endif()
else()
  get_target_property(__boost_headers_alias Boost::headers ALIASED_TARGET)
  set_target_properties("${__boost_headers_alias}" PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__boost_all_includes}")
  if(NOT TARGET Boost::boost)
    add_library(Boost::boost ALIAS "${__boost_headers_alias}")
  endif()
endif()

# optional debug info
if(CPMCACHEBOOST_DEBUG_SHOW_INC_DIRS AND TARGET Boost::headers)
  message(STATUS "cpm cache boost: after adjusting")
  get_target_property(__boost_test_includes Boost::headers INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "cpm cache boost: Boost::headers includes are: ${__boost_test_includes}")
endif()


# run tests if set
if(CPMCACHEBOOST_BUILD_TESTS)
  message(STATUS "cpm cache boost: testing enabled")
  enable_testing()
  add_subdirectory(test)
else()
  message(STATUS "cpm cache boost: testing DISABLED")
endif()
