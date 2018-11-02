
add_executable( mytest mytest.c)

target_link_libraries( mytest btc)
target_include_directories( mytest PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/core/include
)
