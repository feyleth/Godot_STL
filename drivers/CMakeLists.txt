
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
add_element(dummy header cpp)

add_library(${PROJECT_NAME} ${header} ${cpp})


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
