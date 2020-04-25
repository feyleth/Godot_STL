cmake_minimum_required(VERSION 3.5)


set(CMAKE_CXX_STANDARD 17)

project(godot)

#detect platform
set(target)
if(NOT DEFINED ${CMAKE_GENERATOR_PLATFORM})
    # linux
    if(UNIX AND NOT APPLE)
        set(target "linuxbsd")
    endif()
    # apple
    if(APPLE)
        set(target "osx")
    endif()
    # windows
    if(WIN32)
        set(target "windows")
    endif()
    
endif()



#set argument for platform

if(target STREQUAL "linuxbsd")
    find_package(ALSA)
    if(ALSA_FOUND)
        message("Enabling ALSA")
        add_definitions(-DALSA_ENABLED -DALSAMIDI_ENABLED)
    else()
        message("ALSA libraries not found, disabling driver")
    endif()
    
endif()

if(target STREQUAL "osx")
    add_definitions(-DOSX_ENABLED -DUNIX_ENABLED -DAPPLE_STYLE_KEYS -DCOREAUDIO_ENABLED -DCOREMIDI_ENABLED)
endif()


find_package(Python 3.5 COMPONENTS Interpreter REQUIRED)

execute_process(COMMAND ${Python_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/script/make_binders.py"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/script"
)
# TODO: not working 
# add_custom_command(OUTPUT "core/method_bind.gen.inc" "core/method_bind_ext.gen.inc" "core/method_bind_free_func.gen.inc"
#     COMMAND ${Python_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/script/make_binders.py"
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/script"
# )
# add_custom_target(binding DEPENDS "core/method_bind.gen.inc" "core/method_bind_ext.gen.inc" "core/method_bind_free_func.gen.inc")

add_subdirectory(drivers)
