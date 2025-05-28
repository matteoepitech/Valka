file(GLOB_RECURSE MYMEM_SRC src/*.c)

add_library(mymemlib STATIC ${MYMEM_SRC})

target_include_directories(mymemlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
