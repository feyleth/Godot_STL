
project(spirv-reflect)

file(GLOB_RECURSE header "*.h")
file(GLOB_RECURSE cpp "*.c")

add_library(${PROJECT_NAME} ${header} ${cpp})
