#!/bin/bash

OS="$(uname -s)"
mkdir -p build && cd build

# MacOS
if [[ "$OS" == "Darwin" ]]; then
    cmake ..
    cmake --build . -- -j$(sysctl -n hw.ncpu)
    mv ./valkac ../valkac
    printf "\033[32;1mBuild done for MacOS! Usage: ./valkac <file>\033[0m\n"

# Linux
elif [[ "$OS" == "Linux" ]]; then
    cmake ..
    cmake --build . -- -j$(nproc)
    mv ./valkac ../valkac
    printf "\033[32;1mBuild done for Linux! Usage: ./valkac <file>\033[0m\n"

# Windows
elif [[ "$OS" == MINGW* || "$OS" == MSYS* || "$OS" == CYGWIN* ]]; then
    cmake -G "MinGW Makefiles" ..
    cmake --build .
    mv valkac.exe ../valkac.exe
    printf "\033[32;1mBuild done for Windows! Usage: ./valkac.exe <file>\033[0m\n"

else
    echo "Unsupported OS: $OS"
    exit 1
fi
