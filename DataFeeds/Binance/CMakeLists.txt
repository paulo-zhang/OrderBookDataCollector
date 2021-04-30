include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB headers *.h)
file(GLOB cpps *.cpp)
add_library(BinanceDataFeed-objs OBJECT ${cpps} ${headers})

add_library(BinanceDataFeed SHARED $<TARGET_OBJECTS:BinanceDataFeed-objs>)

set_target_properties(BinanceDataFeed
  PROPERTIES
    OUTPUT_NAME "BinanceDataFeed"
  )

# R_X86_64_PC32 against symbol `_ZSt4cout@@GLIBCXX_3.4' can not be used when making a shared object
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O3 -fPIC" )
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )
