include_directories(${CMAKE_SOURCE_DIR})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(Start main.cpp)

target_link_libraries(Start BinanceDataFeed)
