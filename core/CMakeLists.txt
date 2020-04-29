project(godotCore)




set(generateFile)

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/script_encryption_key.gen.cpp"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_key.py"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "${CMAKE_SOURCE_DIR}/script/generat_key.py"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/script_encryption_key.gen.cpp")


option(builtin_certs "Use the built-in SSL certificates bundles" ON)
set(system_certs_path "" CACHE STRING "Use this path as SSL certificates default for editor (for package maintainers)")
add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/io/certs_compressed.gen.h"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_certs_header.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/io/certs_compressed.gen.h"
    "../thirdparty/certs/ca-certificates.crt"
    " ${system_certs_path}"
    "${builtin_certs}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "../thirdparty/certs/ca-certificates.crt"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/io/certs_compressed.gen.h")

# TODO: put method_bind in this

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/authors.gen.h"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_authors_header.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/authors.gen.h"
    "${CMAKE_SOURCE_DIR}/AUTHORS.md"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "${CMAKE_SOURCE_DIR}/AUTHORS.md"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/authors.gen.h")


add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/donors.gen.h"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_authors_header.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/donors.gen.h"
    "${CMAKE_SOURCE_DIR}/DONORS.md"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "${CMAKE_SOURCE_DIR}/DONORS.md"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/donors.gen.h")


add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/license.gen.h"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_authors_header.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/license.gen.h"
    "${CMAKE_SOURCE_DIR}/COPYRIGHT.txt"
    "${CMAKE_SOURCE_DIR}/LICENSE.txt"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "${CMAKE_SOURCE_DIR}/COPYRIGHT.txt"
    "${CMAKE_SOURCE_DIR}/LICENSE.txt"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/license.gen.h")


set(mappings "${CMAKE_CURRENT_SOURCE_DIR}/input/gamecontrollerdb_204.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/input/gamecontrollerdb_205.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/input/gamecontrollerdb.txt" 
    "${CMAKE_CURRENT_SOURCE_DIR}/input/godotcontrollerdb.txt")

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/input/default_controller_mappings.gen.cpp"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_default_controller_mappings.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/input/default_controller_mappings.gen.cpp"
    "\"${mappings}\""
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core/input"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/input/default_controller_mappings.gen.cpp")

add_library(${PROJECT_NAME} ${generateFile})

# TODO: suppress
target_include_directories(${PROJECT_NAME} PRIVATE "../")
target_include_directories(${PROJECT_NAME} PRIVATE "../platform/${target}")

target_link_libraries(${PROJECT_NAME} PRIVATE misc)
target_link_libraries(${PROJECT_NAME} PRIVATE zlib)
target_link_libraries(${PROJECT_NAME} PRIVATE minizip)
target_link_libraries(${PROJECT_NAME} PRIVATE zstd)
target_link_libraries(${PROJECT_NAME} PRIVATE mbedtls)
