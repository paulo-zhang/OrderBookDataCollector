cmake_minimum_required(VERSION 3.14)
project(RedisStorageTest)

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  RedisStorageTest
  RedisStorageTest.cpp
)
target_link_libraries(
  RedisStorageTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(RedisStorageTest)

target_link_libraries(RedisStorageTest RedisStorage)