# https://github.com/sewenew/redis-plus-plus

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB headers *.h)
file(GLOB cpps *.cpp)
add_library(RedisStorage-objs OBJECT ${cpps} ${headers})

add_library(RedisStorage SHARED $<TARGET_OBJECTS:RedisStorage-objs>)

set_target_properties(RedisStorage
  PROPERTIES
    OUTPUT_NAME "RedisStorage"
  )

# R_X86_64_PC32 against symbol `_ZSt4cout@@GLIBCXX_3.4' can not be used when making a shared object
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++17 -O3 -fPIC" )
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )