include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB headers *.h)
file(GLOB cpps *.cpp)
add_library(BinanceDataFeed SHARED ${cpps} ${headers})

add_definitions(-DEXPMODULE)

target_link_libraries(BinanceDataFeed debug BinanceDataFeed.lib)
target_link_libraries(BinanceDataFeed optimized BinanceDataFeed.lib)