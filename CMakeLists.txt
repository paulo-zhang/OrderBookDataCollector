cmake_minimum_required(VERSION 3.0.0)
project(OrderBookDataCollector VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_subdirectory(Start)
add_subdirectory(DataFeeds/Binance)
add_subdirectory(Storages/Redis)
add_subdirectory(Storages/MongoDB)

add_subdirectory(Tests/DataFeeds/BinanceTest)
add_subdirectory(Tests/Storages/MongoDBStorageTest)
add_subdirectory(Tests/Storages/RedisStorageTest)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Start)
