cmake_minimum_required(VERSION 3.10)
project(ValkaC LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/memory_lib/include
)

add_subdirectory(lib/memory_lib)

file(GLOB_RECURSE VALKA_SRC src/*.c)

add_executable(valkac ${VALKA_SRC})

target_link_libraries(valkac PRIVATE mymemlib)
