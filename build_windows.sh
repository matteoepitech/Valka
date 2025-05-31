# Creation of the build folder
mkdir -p build && cd build

# CMake build
cmake -G "MinGW Makefiles" ..
cmake --build .

# Move binary in main folder (will be removed)
mv valkac.exe ../valkac.exe
printf "\033[32;1mBuild done! Usage: ./valkac.exe <file>\033[0m\n"
