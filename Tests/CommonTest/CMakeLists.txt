cmake_minimum_required(VERSION 3.14)
project(OrderBookTest)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties)
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
    OrderBookTest
    OrderBookTest.cpp
)
target_link_libraries(
    OrderBookTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(OrderBookTest)
