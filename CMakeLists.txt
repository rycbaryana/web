cmake_minimum_required(VERSION 3.13)

project(http-server-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

file(GLOB_RECURSE TEST_SOURCES src/*_test.cpp)

list(REMOVE_ITEM SOURCE_FILES ${TEST_SOURCES})

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

find_package(Catch2 3 REQUIRED)

add_executable(server ${SOURCE_FILES})
add_executable(tests ${TEST_SOURCES})

target_link_libraries(server PRIVATE Threads::Threads ZLIB::ZLIB)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
