

file(GLOB SOURCE_FILES "*.h" "*.c")

add_library( eos_btc ${SOURCE_FILES} )


target_link_libraries( eos_btc
        extrenals/secp256k1/.libs/libsecp256k1.a
        )


target_include_directories( eos_btc
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_BINARY_DIR}/include"
        "${CMAKE_SOURCE_DIR}/extrenals/secp256k1/src"
        )
