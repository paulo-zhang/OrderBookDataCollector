include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties ${CMAKE_SOURCE_DIR}/ThirdParties/asio-1.18.1 /usr/include)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB headers *.h)
file(GLOB cpps *.cpp)
add_library(PlatformService-objs OBJECT ${cpps} ${headers})

add_library(PlatformService SHARED $<TARGET_OBJECTS:PlatformService-objs>)

set_target_properties(PlatformService
  PROPERTIES
    OUTPUT_NAME "PlatformService"
  )

# relocation R_X86_64_PC32 against symbol `_ZSt4cout@@GLIBCXX_3.4' can not be used when making a shared object; recompile with -fPIC
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++17 -O3 -fPIC" )
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )