cmake_minimum_required(VERSION 3.25)
project(CppUtestPlay)

add_executable(TestRunnerMainA)
target_sources(TestRunnerMainA
  PRIVATE
    cpputest/tests/test_runner_main_A.cpp
    cpputest/tests/test_this-fails.cpp
)
target_link_libraries(TestRunnerMainA 
    PUBLIC 
        CppUTest
        CppUTestExt
)


add_executable(TestRunnerMainB)
target_sources(TestRunnerMainB
  PRIVATE
    cpputest/tests/test_runner_main_A.cpp
    cpputest/tests/test_using_crc_lib.cpp
)
target_link_libraries(TestRunnerMainB 
    PUBLIC 
        CppUTest
        CppUTestExt
)