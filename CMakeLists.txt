cmake_minimum_required(VERSION 3.10)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DashPlus)

find_package(Threads REQUIRED)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie") 
endif()

if(APPLE)
    message("Detected platform APPLE. Linking required libraries.")
    find_library(COCOA_LIBRARY Cocoa)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(GLFW_LIBRARY glfw)
    find_library(OPENGL_LIBRARY OpenGL)

    if(NOT COCOA_LIBRARY)
        message(FATAL_ERROR "Cocoa Not Found.")
    endif()
    message("Found Cocoa at " ${COCOA_LIBRARY})
    if(NOT COREVIDEO_LIBRARY)
        message(FATAL_ERROR "CoreVideo Not Found.")
    endif()
    message("Found CoreVideo at " ${COREVIDEO_LIBRARY})
    if(NOT IOKIT_LIBRARY)
        message(FATAL_ERROR "IOKit Not Found.")
    endif()
    message("Found IOKit at " ${IOKIT_LIBRARY})
    if(NOT GLFW_LIBRARY)
        message(FATAL_ERROR "GLFW Not Found.")
    endif()
    message("Found GLFW at " ${GLFW_LIBRARY})
    if(NOT OPENGL_LIBRARY)
    message(FATAL_ERROR "OpenGL Not Found.")
    endif()
    message("Found OpenGL at " ${OPENGL_LIBRARY})
else()

endif()

FILE(GLOB DASHPLUS_SOURCES cpp/*.cpp)

add_executable(DashPlus main.cpp ${DASHPLUS_SOURCES})
target_include_directories(DashPlus PUBLIC
                           ${PROJECT_SOURCE_DIR}/include                           
                           ${PROJECT_SOURCE_DIR}/raylib/build/raylib/include
                          )

if(APPLE)
    target_link_libraries(DashPlus ${PROJECT_SOURCE_DIR}/raylib/build/raylib/libraylib.a dl ${CMAKE_THREAD_LIBS_INIT} ${COCOA_LIBRARY} ${COREVIDEO_LIBRARY} ${IOKIT_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARY})
endif()
if(UNIX)
    target_link_libraries(DashPlus ${PROJECT_SOURCE_DIR}/raylib/build/raylib/libraylib.a dl ${CMAKE_THREAD_LIBS_INIT})
endif()
if(MSVC)
    target_link_libraries(DashPlus ${PROJECT_SOURCE_DIR}/raylib/build/raylib/Release/raylib.lib ${CMAKE_THREAD_LIBS_INIT})
endif()

