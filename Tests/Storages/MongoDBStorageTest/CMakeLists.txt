cmake_minimum_required(VERSION 3.14)
project(MongoDBStorageTest)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/ThirdParties)
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

add_executable(
  ${PROJECT_NAME}
  MongoDBStorageTest.cpp
)
target_link_libraries(
  ${PROJECT_NAME}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} MongoDBStorage)

# MongoDB
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} mongo::bsoncxx_shared)
target_link_libraries(${PROJECT_NAME} mongo::mongocxx_shared)
