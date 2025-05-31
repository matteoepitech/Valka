# Creation of the build folder
mkdir -p build && cd build

# CMake build
cmake ..
cmake --build . -- -j16

# Move binary in main folder (will be removed)
mv ./valkac ../valkac
printf "\033[32;1mBuild done! Usage: ./valkac <file>\033[0m\n"
