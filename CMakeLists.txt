cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

find_package(Python 3.5 COMPONENTS Interpreter REQUIRED)

include(cmake/compilegles.cmake)
include(cmake/generatVersion.cmake)

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
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG_ENABLED)
        add_link_options(-rdynamic)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-DDEBUG_MEMORY_ENABLED)
endif()


if(target STREQUAL "linuxbsd")

    option(touch "Enable touch events" ON)

    find_package(ALSA)
    if(ALSA_FOUND)
        message("Enabling ALSA")
        add_definitions(-DALSA_ENABLED -DALSAMIDI_ENABLED)
    else()
        message("ALSA libraries not found, disabling driver")
    endif()

    find_package(PulseAudio)
    if(PulseAudio_FOUND)
        message("Enabling PulseAudio")
        add_definitions(-DPULSEAUDIO_ENABLED)
    else()
        message("PulseAudio development libraries not found, disabling driver")
    endif()
    
    find_package(Udev)
    if(PulseAudio_FOUND)
        message("Enabling udev support")
        add_definitions(-DUDEV_ENABLED)
    else()
        message("libudev development libraries not found, disabling udev support")
    endif()

    find_package(X11 REQUIRED)

    # TODO: see for cmake
    # env.ParseConfig("pkg-config xcursor --cflags --libs")
    # env.ParseConfig("pkg-config xinerama --cflags --libs")
    # env.ParseConfig("pkg-config xrandr --cflags --libs")
    # env.ParseConfig("pkg-config xrender --cflags --libs")
    # env.ParseConfig("pkg-config xi --cflags --libs")
    # env.Append(CPPDEFINES=['OPENGL_ENABLED'])

    # TODO: only lvm test gcc
    #add_definitions(-DTYPED_METHOD_BIND)

    if(touch)
        add_definitions(-DTOUCH_ENABLED)
    endif()
    

    add_definitions(-DJOYDEV_ENABLED)
    add_definitions(-DX11_ENABLED -DUNIX_ENABLED)
    add_definitions(-DVULKAN_ENABLED)
endif()

if(target STREQUAL "osx")
    add_definitions(-DOSX_ENABLED -DUNIX_ENABLED -DAPPLE_STYLE_KEYS -DCOREAUDIO_ENABLED -DCOREMIDI_ENABLED)
endif()

if(target STREQUAL "Android")
    option(android_neon "Enable NEON support (armv7 only)" True)

    set(android_arch "armv7" CACHE STRING "Target architecture")
    set_property(CACHE android_arch PROPERTY STRINGS "armv7" "arm64v8" "x86" "x86_64")
    
    set(use_neon OFF)
    if(android_arch STREQUAL "armv7")
        set(use_neon android_neon)
    endif()
    
endif()



find_file(file mntent.h)
if( NOT file-NOTFOUND)
    add_definitions(-DHAVE_MNTENT)
endif()

execute_process(COMMAND ${Python_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/script/make_binders.py"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/script"
)
# TODO: not working 
# add_custom_command(OUTPUT "core/method_bind.gen.inc" "core/method_bind_ext.gen.inc" "core/method_bind_free_func.gen.inc"
#     COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/make_binders.py"
#     WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/script"
# )
# add_custom_target(binding DEPENDS "core/method_bind.gen.inc" "core/method_bind_ext.gen.inc" "core/method_bind_free_func.gen.inc")

add_subdirectory(thirdparty)

add_subdirectory(drivers)
add_subdirectory(core)
