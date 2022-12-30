cmake_minimum_required(VERSION 3.14)
project(cpm-cache-boost
    VERSION 1.8.1
    LANGUAGES CXX
)
# CPM
include(cmake/CPM.cmake)
# boost
CPMAddPackage(
  NAME Boost
  GITHUB_REPOSITORY boostorg/boost
  GIT_TAG boost-1.81.0
  VERSION 1.81.0
)
