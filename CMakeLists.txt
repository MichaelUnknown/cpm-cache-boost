cmake_minimum_required(VERSION 3.14)
project(cpm-cache-boost
    VERSION 1.82.0
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
  GIT_TAG boost-1.82.0
  VERSION 1.82.0
)

# with 1.82.0 there is (still?) no Boost::boost target - adding for compatibility
if(NOT TARGET Boost::boost)
    message(STATUS " CPMCACHEBOOST: manually adding Boost::boost")
    add_library(Boost::boost INTERFACE IMPORTED)
    target_link_libraries(Boost::boost INTERFACE Boost::headers)
endif()


## https://stackoverflow.com/questions/32183975/how-to-print-all-the-properties-of-a-target-in-cmake/56738858#56738858
## Get all properties that cmake supports
execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
## Convert command output into a CMake list
STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
list(REMOVE_DUPLICATES CMAKE_PROPERTY_LIST)
function(print_target_properties tgt)
    if(NOT TARGET ${tgt})
      message("There is no target named '${tgt}'")
      return()
    endif()
    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        get_target_property(propval ${tgt} ${prop})
        if (propval)
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(print_target_properties)


# check targets if tests is set
if(CPMCACHEBOOST_BUILD_TESTS)
    print_target_properties(Boost::headers)
    print_target_properties(Boost::boost)
endif()

# run tests if set
if(CPMCACHEBOOST_BUILD_TESTS)
    message(STATUS "cpm cache boost: testing enabled")
    enable_testing()
    add_subdirectory(test)
else()
    message(STATUS "cpm cache boost: testing DISABLED")
endif()
