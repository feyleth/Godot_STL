
macro(add_element dir header cpp)

file(GLOB_RECURSE tmp_header "${dir}/*.h")
file(GLOB_RECURSE tmp_cpp "${dir}/*.cpp")

list(APPEND header ${tmp_header})
list(APPEND cpp ${tmp_cpp})

endmacro()


project(godotDriver)

set(header)
set(cpp)

add_element(alsa header cpp)
add_element(alsamidi header cpp)
add_element(coreaudio header cpp)
set(list "server" "javascript")
list(FIND list ${target} res)
if(${res} EQUAL -1)
    add_element(dummy header cpp)
endif()

# TODO: implement
set(gen)
# add_element(gles2 header cpp)
# compilegles("gles2/shaders/copy" gen)
# # compilegles("gles2/shaders/resolve" gen)
# compilegles("gles2/shaders/canvas" gen)
# compilegles("gles2/shaders/canvas_shadow" gen)
# compilegles("gles2/shaders/scene" gen)
# compilegles("gles2/shaders/cubemap_filter" gen)
# compilegles("gles2/shaders/cube_to_dp" gen)
# # compilegles("gles2/shaders/blend_shape" gen)
# # compilegles("gles2/shaders/screen_space_reflection" gen)
# compilegles("gles2/shaders/effect_blur" gen)
# # compilegles("gles2/shaders/subsurf_scattering" gen)
# # compilegles("gles2/shaders/ssao" gen)
# # compilegles("gles2/shaders/ssao_minify" gen)
# # compilegles("gles2/shaders/ssao_blur" gen)
# # compilegles("gles2/shaders/exposure" gen)
# compilegles("gles2/shaders/tonemap" gen)
# # compilegles("gles2/shaders/particles" gen)
# compilegles("gles2/shaders/lens_distorted" gen)

add_element(png header cpp)
add_element(pulseaudio header cpp)

add_library(${PROJECT_NAME} ${header} ${cpp} ${gen})


# TODO : remove 
# alsa : #include "core/os/mutex.h"
target_include_directories(${PROJECT_NAME} PRIVATE "../")
target_include_directories(${PROJECT_NAME} PRIVATE "../platform/${target}")


#gl_context
set(list "haiku" "osx" "windows" "linuxbsd")
list(FIND list ${target} res)
if(NOT ${res} EQUAL -1)
    target_link_libraries(${PROJECT_NAME} PUBLIC glad)
endif()

# libpng
target_link_libraries(${PROJECT_NAME} PUBLIC png)
#spirv-reflect
target_link_libraries(${PROJECT_NAME} PUBLIC spirv-reflect)
