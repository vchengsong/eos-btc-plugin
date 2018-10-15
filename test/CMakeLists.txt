
add_executable( testt test.c)

target_link_libraries( testt
#        ${CMAKE_SOURCE_DIR}/extrenals/secp256k1/.libs/libsecp256k1.a
        ${CMAKE_SOURCE_DIR}/build/libraries/core/libbtc.a
        )

target_include_directories( testt PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/core/include
)
