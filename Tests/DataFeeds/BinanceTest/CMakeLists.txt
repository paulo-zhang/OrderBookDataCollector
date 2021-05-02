cmake_minimum_required(VERSION 3.14)
project(BinanceTest)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties ${CMAKE_SOURCE_DIR}/ThirdParties/asio-1.18.1 /usr/include/)
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

file(GLOB cpps *.cpp)
add_executable(BinanceTest ${cpps})

target_link_libraries(
    BinanceTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(BinanceTest)

# $sudo apt-get install libboost-all-dev
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.71.0 COMPONENTS system thread)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(BinanceTest ${Boost_LIBRARIES})
endif()

# $sudo apt-get install libssl-dev
# OpenSSL, https://stackoverflow.com/questions/45548088/include-openssl-in-a-cmakelist-txt-file
find_package(OpenSSL REQUIRED) 

target_link_libraries(BinanceTest BinanceDataFeed OpenSSL::SSL)