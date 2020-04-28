macro(compilegles source gen)
list(APPEND gen "${CMAKE_CURRENT_SOURCE_DIR}/${source}.glsl.gen.h")
add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${source}.glsl.gen.h"
     COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/build_gles2_headers.py" "${CMAKE_CURRENT_SOURCE_DIR}/${source}.glsl"
     DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${source}.glsl"
     WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/script"
)
endmacro()
