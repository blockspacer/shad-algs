cmake_minimum_required(VERSION 2.8)
project(calculator)

if (TEST_SOLUTION)
  include_directories(../private/calculator)
endif()

include(../../common.cmake)

if (ENABLE_PRIVATE_TESTS)

endif()

add_executable(task task4.cpp)
