

file(GLOB SOURCE_FILES "*.c")

add_library( btc ${SOURCE_FILES} )

target_include_directories( btc
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/extrenals"
    "${CMAKE_SOURCE_DIR}/extrenals/secp256k1"
)
