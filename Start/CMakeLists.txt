include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties ${CMAKE_SOURCE_DIR}/ThirdParties/asio-1.18.1)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB cpps *.cpp)
add_executable(Start ${cpps})

target_link_libraries(Start BinanceDataFeed RedisStorage MongoDBStorage)
