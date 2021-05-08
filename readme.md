# DashPlus

A customisable FRC Driver Station Dashboard for the New WPILIB Framework.

## Setting up Build Environment
Tested working on Ubuntu, macOS and Windows.
Sadly the MSVC (Microsoft) compiler isn't as nice with the program, and it hasn't had enough work yet to confirm full functionality. It should be useable, however. See the instructions below to build.

Unix Instructions:
```bash
# If you are on Ubuntu
sudo apt install cmake build-essential ninja-build libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libopencv-dev freeglut3-dev
# Otherwise, for Mac, use MacPorts or Homebrew to pull down the required libraries.

git clone --recursive https://github.com/mitchellblaser/dashplus
cd dashplus

cd allwpilib
mkdir build && cd build
cmake .. -DWITH_JAVA=OFF -DWITH_TESTS=OFF -DWITH_SIMULATION_MODULES=OFF -DWITH_CSCORE=OFF -DWITH_GUI=OFF
make
cd ..

cd raylib
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=OFF
make
cd ..

mkdir build && cd build
cmake ..
make
```


Windows Instructions:

Depends on: Python 3, CMake, Git for Windows.
```powershell
git clone --recursive https://github.com/mitchellblaser/dashplus
cd dashplus

cd allwpilib
mkdir build && cd build
cmake .. -DWITH_JAVA=OFF -DWITH_TESTS=OFF -DWITH_SIMULATION_MODULES=OFF -DWITH_CSCORE=OFF -DWITH_GUI=OFF
devenv /Build Release allwpilib.sln
cd ..

cd raylib
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=OFF -DCUSTOMIZE_BUILD=ON -DUSE_AUDIO=OFF
devenv /Build Release raylib.sln
cd ..

mkdir build && cd build
cmake ..
devenv /Build Release DashPlus.sln
./Release/DashPlus.exe

```
