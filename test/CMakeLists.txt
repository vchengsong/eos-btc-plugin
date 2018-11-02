
add_executable( test test.c)

target_link_libraries( test btc)
target_include_directories( test PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/core/include
)
