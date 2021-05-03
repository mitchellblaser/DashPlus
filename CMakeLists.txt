cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DashPlus)

find_package(Threads REQUIRED)

add_executable(DashPlus main.cpp)
target_include_directories(DashPlus PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/raylib/build/raylib/include
                          )

target_link_libraries(DashPlus ${PROJECT_SOURCE_DIR}/raylib/build/raylib/libraylib.a dl ${CMAKE_THREAD_LIBS_INIT})