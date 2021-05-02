include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties ${CMAKE_SOURCE_DIR}/ThirdParties/asio-1.18.1 /usr/include)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB cpps *.cpp)
add_executable(Start ${cpps})

# $sudo apt-get install libboost-all-dev
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.71.0 COMPONENTS system thread)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(Start ${Boost_LIBRARIES})
endif()

# $sudo apt-get install libssl-dev
# OpenSSL, https://stackoverflow.com/questions/45548088/include-openssl-in-a-cmakelist-txt-file
find_package(OpenSSL REQUIRED) 

target_link_libraries(Start BinanceDataFeed RedisStorage MongoDBStorage OpenSSL::SSL)
