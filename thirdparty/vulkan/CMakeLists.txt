project(vulkan)

file(GLOB header "*.h")
file(GLOB c "*.cpp")

file(GLOB_RECURSE loader_header "loader/*.h")
file(GLOB_RECURSE loader_cpp "loader/*.c")

if(target STREQUAL "android")
    file(GLOB_RECURSE android_header "android/*.h")
    file(GLOB_RECURSE android_cpp "android/*.c")
    list(APPEND header android_header)
    list(APPEND cpp android_cpp)
endif()

if(NOT target STREQUAL "windows")
    list(REMOVE_ITEM loader_header "${CMAKE_CURRENT_SOURCE_DIR}/loader/dirent_on_windows.h" "${CMAKE_CURRENT_SOURCE_DIR}/loader/dxgi_loader.h")
    list(REMOVE_ITEM loader_cpp "${CMAKE_CURRENT_SOURCE_DIR}/loader/dirent_on_windows.c" "${CMAKE_CURRENT_SOURCE_DIR}/loader/dxgi_loader.c")
endif()


add_library(${PROJECT_NAME} ${header} ${c} ${loader_header} ${loader_cpp})

target_include_directories(${PROJECT_NAME} PUBLIC ".")

target_include_directories(${PROJECT_NAME} PUBLIC "./include"
    "./loader"
)

if(target STREQUAL "android")
    target_include_directories(${PROJECT_NAME} PUBLIC ${ANDROID_NDK_ROOT}
        ${ANDROID_NDK_ROOT}/include
        ${ANDROID_NDK_ROOT}/layers
        ${ANDROID_NDK_ROOT}/layers/generated
    )
endif()
if(target STREQUAL "windows")
    target_compile_options(${PROJECT_NAME} PRIVATE -DVK_USE_PLATFORM_WIN32_KHR
        -DVULKAN_NON_CMAKE_BUILD
        -DWIN32_LEAN_AND_MEAN
        -DAPI_NAME="Vulkan"
    )

    # Windows 7+, missing in mingw headers
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE -DCM_GETIDLIST_FILTER_CLASS=0x00000200
            -DCM_GETIDLIST_FILTER_PRESENT=0x00000100
        )
    endif()
    
endif()
if(target STREQUAL "osx")
    target_compile_options(${PROJECT_NAME} PRIVATE -DVK_USE_PLATFORM_MACOS_MVK
        -DVULKAN_NON_CMAKE_BUILD
        -DSYSCONFDIR="/etc"
        -DFALLBACK_DATA_DIRS="/usr/local/share:/usr/share"
        -DFALLBACK_CONFIG_DIRS="/etc/xdg"
    )
endif()
if(target STREQUAL "iphone")
    target_compile_options(${PROJECT_NAME} PRIVATE -DVK_USE_PLATFORM_IOS_MVK
        -DVULKAN_NON_CMAKE_BUILD
        -DSYSCONFDIR="/etc"
        -DFALLBACK_DATA_DIRS="/usr/local/share:/usr/share"
        -DFALLBACK_CONFIG_DIRS="/etc/xdg"
    )
endif()
if(target STREQUAL "linuxbsd")
    target_compile_options(${PROJECT_NAME} PRIVATE -DVK_USE_PLATFORM_XLIB_KHR
        -DVULKAN_NON_CMAKE_BUILD
        -DSYSCONFDIR="/etc"
        -DFALLBACK_DATA_DIRS="/usr/local/share:/usr/share"
        -DFALLBACK_CONFIG_DIRS="/etc/xdg"
    )
    if(UNIX)
        target_compile_options(${PROJECT_NAME} PRIVATE -DHAVE_SECURE_GETENV)
    endif()
    
endif()
