CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (NLE)

set (NLE_VERSION_MAJOR 1)
set (NLE_VERSION_MINOR 0)
set (NLE_VERSION_PATCH 0)

add_subdirectory (NLCore)
include_directories(NLCore)

add_executable (NLE NLCore NLE.cpp)

target_link_libraries (NLE NLCore)

install (TARGETS NLE DESTINATION bin)