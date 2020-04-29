
add_definitions(-w)

add_subdirectory(glad)
add_subdirectory(libpng)
add_subdirectory(spirv-reflect)
add_subdirectory(vulkan)
add_subdirectory(misc)
add_subdirectory(zlib)


remove_definitions(-w)