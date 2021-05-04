cmake_minimum_required(VERSION 3.10)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DashPlus)

find_package(Threads REQUIRED)

FILE(GLOB DASHPLUS_SOURCES cpp/*.cpp)

add_executable(DashPlus main.cpp ${DASHPLUS_SOURCES})
target_include_directories(DashPlus PUBLIC
                           ${PROJECT_SOURCE_DIR}/include                           
                           ${PROJECT_SOURCE_DIR}/raylib/build/raylib/include
                          )

target_link_libraries(DashPlus ${PROJECT_SOURCE_DIR}/raylib/build/raylib/libraylib.a dl ${CMAKE_THREAD_LIBS_INIT})