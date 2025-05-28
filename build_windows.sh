# Creation of the build folder
mkdir -p build && cd build

# CMake build
cmake ..
cmake --build .

# Move binary in main folder (will be removed)
move valkac ..\valkac
