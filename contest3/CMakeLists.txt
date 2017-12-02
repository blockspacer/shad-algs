cmake_minimum_required(VERSION 2.8)
project(FootballPlayers)

if (TEST_SOLUTION)
  include_directories()
endif()

include(../../common.cmake)

if (ENABLE_PRIVATE_TESTS)

endif()

add_executable(task FootballPlayers.cpp)
