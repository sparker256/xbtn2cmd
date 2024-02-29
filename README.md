Xbtn2cmd for X-Plane 12
=========================

[![CMake](https://github.com/sparker256/xbtn2cmd/actions/workflows/cmake.yml/badge.svg)](https://github.com/sparker256/xbtn2cmd/actions/workflows/cmake.yml)

![Alt text](pics/Xbtn2cmd_Page1.jpg?raw=true "Xbtn2cmd")

X-Plane 12 Window API to map buttons to commands in VR

## Building Xbtn2cmd from source

### On windows

1.  Install required software using [Chocolatey](https://chocolatey.org/) using admin command prompt:

    ```
    choco install git
    choco install cmake --installargs '"ADD_CMAKE_TO_PATH=System"'
    choco install mingw --version 8.1.0
    ```

    You can also install the same programs manually if you prefer.

2.  Checkout and configure the project:

    ```
    git clone https://github.com/sparker256/xbtn2cmd.git
    cd xbtn2cmd
    cmake -G "MinGW Makefiles" -S .\src -B .\build -DCMAKE_BUILD_TYPE=RelWithDebInfo
    ```

3.  Build the project and copy the plugin DLL into the appropriate directory:

    ```
    cmake --build .\build
    cp .\build\win.xpl .\Xbtn2cmd\64\
    ```

### On Ubuntu:

1. Install required software:

   ```
   sudo apt-get install -y --no-install-recommends build-essential cmake git freeglut3-dev libudev-dev libopenal-dev

   ```

2. Checkout and configure the project:

   ```
   git clone https://github.com/sparker256/xbtn2cmd.git
   cd xbtn2cmd
   cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=RelWithDebInfo
   ```

3. Build the project and copy the plugin DLL into the appropriate directory:

   ```
   cmake --build ./build
   mkdir ./Xbtn2cmd/64
   cp ./build/lin.xpl ./Xbtn2cmd/64/
   ```

### On OS X:

1. Install XCode, Git, CMake (Homebrew can be convenient for this).

2. Checkout and configure the project:

   ```
   git clone https://github.com/sparker256/xbtn2cmd.git
   cd xbtn2cmd
   cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=RelWithDebInfo
   ```

3. Build the project and copy the plugin DLL into the appropriate directory:

   ```
   cmake --build ./build
   mkdir ./Xbtn2cmd/64
   cp ./build/mac.xpl ./Xbtn2cmd/64/
   ```

