cmake_minimum_required(VERSION 3.25)
project(cpputest)

find_package(Catch2 REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/deps/Catch2")
add_executable(testC testCatch2.cpp)
target_link_libraries(testC
    PRIVATE
        Catch2::Catch2WithMain
)