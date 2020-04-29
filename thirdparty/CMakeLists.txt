
add_definitions(-w)

add_subdirectory(glad)
add_subdirectory(libpng)
add_subdirectory(spirv-reflect)
add_subdirectory(vulkan)
add_subdirectory(misc)
add_subdirectory(zlib)
add_subdirectory(minizip)
add_subdirectory(zstd)

remove_definitions(-w)