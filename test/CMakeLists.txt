cmake_minimum_required(VERSION 3.20)

set(This ExampleTests)

set(TestSources Tests.cpp)

set(TestMethods test_src/Methods.c
                test_src/Methods.h)

add_executable(${This} ${TestSources} ${Sources} ${TestMethods})

target_link_libraries(${This} PUBLIC gtest_main)

add_test(
  NAME ${This}
  COMMAND ${This}
)