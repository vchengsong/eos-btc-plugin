

file(GLOB SOURCE_FILES "*.c")

add_library( btc ${SOURCE_FILES} )

#target_link_libraries( btc ${CMAKE_SOURCE_DIR}/extrenals/secp256k1/.libs/libeos_btc.a )

target_include_directories( btc
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}/include"
    "${CMAKE_SOURCE_DIR}/extrenals"
    "${CMAKE_SOURCE_DIR}/extrenals/secp256k1"
)
