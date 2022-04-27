cmake_minimum_required(VERSION 3.20)

set(This ExampleTests)

set(TestSources Event.Tests.cpp)

set(TestMethods event_helpers/Methods.c
                event_helpers/Methods.h)

add_executable(${This} ${TestSources} ${Sources} ${TestMethods})

target_link_libraries(${This} PUBLIC gtest_main)

add_test(
  NAME ${This}
  COMMAND ${This}
)