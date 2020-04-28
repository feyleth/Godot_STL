
project(png)

file(GLOB header "*.h")
file(GLOB cpp "*.c")

set(arm)
if(use_neon)
    file(GLOB arm "arm/*.c")
    file(APPREND amr "arm/filter_neon.S")
endif()

add_library(${PROJECT_NAME} ${header} ${cpp} ${arm})

if(android_neon)
    target_compile_options(${PROJECT_NAME} PRIVATE -DPNG_ARM_NEON_OPT=2)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -DPNG_ARM_NEON_OPT=0)
endif()