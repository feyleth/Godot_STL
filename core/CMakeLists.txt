project(godotCore)




set(generateFile)

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/script_encryption_key.gen.cpp"
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_key.py"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/core"
    DEPENDS "${CMAKE_SOURCE_DIR}/script/generat_key.py"
)
list(APPEND generateFile "${CMAKE_CURRENT_SOURCE_DIR}/script_encryption_key.gen.cpp")

add_library(${PROJECT_NAME} ${generateFile})

# TODO: suppress
target_include_directories(${PROJECT_NAME} PRIVATE "../")
target_include_directories(${PROJECT_NAME} PRIVATE "../platform/${target}")

target_link_libraries(${PROJECT_NAME} PRIVATE misc)
target_link_libraries(${PROJECT_NAME} PRIVATE zlib)
target_link_libraries(${PROJECT_NAME} PRIVATE minizip)
target_link_libraries(${PROJECT_NAME} PRIVATE zstd)

