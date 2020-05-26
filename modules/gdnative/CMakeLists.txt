project(module_gdnative)

file(GLOB_RECURSE header "*.h")
file(GLOB_RECURSE cpp "*.cpp")

set(generate "${CMAKE_CURRENT_SOURCE_DIR}/include/gdnative_api_struct.gen.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/gdnative_api_struct.gen.cpp")

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/include/gdnative_api_struct.gen.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/gdnative_api_struct.gen.cpp"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/script/generate_gdnative_api.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/gdnative_api_struct.gen.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/gdnative_api_struct.gen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gdnative_api.json"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/script"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/gdnative_api.json"
	)

add_library(${PROJECT_NAME} ${header} ${cpp} ${generate})

# TODO : ???
#     env.Append(LINKFLAGS=["-rdynamic"])

target_compile_definitions(${PROJECT_NAME} PUBLIC -DPTRCALL_ENABLED)

target_link_libraries(${PROJECT_NAME} PRIVATE godotCore godotScene)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")

if(${module_webrtc})
    target_include_directories(${PROJECT_NAME} PRIVATE -DWEBRTC_GDNATIVE_ENABLED)
endif()
