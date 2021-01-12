message("DashPlus Path: '" $ENV{dashplus_path} "'")

cmake_minimum_required (VERSION 2.8)

project(dashplus)

include_directories($ENV{dashplus_path}/allwpilib-2021.1.2/ntcore/src/main/native/include/ $ENV{dashplus_path}/allwpilib-2021.1.2/wpiutil/src/main/native/include/ $ENV{dashplus_path}/raylib/build/src $ENV{dashplus_path}/raylib)

add_executable(dashplus main.cpp )

target_link_libraries(dashplus $ENV{dashplus_path}/allwpilib-2021.1.2/build/lib/libntcore.so $ENV{dashplus_path}/raylib/build/src/libraylib.so) 

add_definitions(-Wall -std=c++17 -lstdc++ -lntcore -lopencv_highgui -lopencv_core -lraylib -lglfw3 -lGL -lopenal -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor)

