cmake_minimum_required(VERSION 3.25)
project(cpputest)

add_executable(testRunA)

target_sources(testRunA
    PRIVATE
        tests/testrunnerA.cpp
)
