# https://github.com/zaphoyd/websocketpp
# https://sourceforge.net/projects/asio/files/asio/1.18.1%20%28Stable%29/ (https://udomain.dl.sourceforge.net/project/asio/asio/1.18.1%20%28Stable%29/asio-1.18.1.tar.gz)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties ${CMAKE_SOURCE_DIR}/ThirdParties/asio-1.18.1 /usr/include)
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
# -pthread, https://stackoverflow.com/questions/34933042/undefined-reference-to-pthread-create-error-when-making-c11-application-with
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++17 -O3 -fPIC -pthread" ) 
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )
