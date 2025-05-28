# Creation of the build folder
mkdir -p build && cd build

# CMake build
cmake -G "MinGW Makefiles" ..
cmake --build .

# Move binary in main folder (will be removed)
mv valkac.exe ../valkac.exe
