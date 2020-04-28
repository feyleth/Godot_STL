macro(generatVersion versionfile)
set(versionfile "${CMAKE_SOURCE_DIR}/core/version_generated.gen.h")
set(hashversion "${CMAKE_SOURCE_DIR}/core/version_hash.gen.h")
add_custom_command(OUTPUT ${versionfile} ${hashversion}
    COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/script/generat_version.py"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    DEPENDS "${CMAKE_SOURCE_DIR}/script/generat_version.py"
)
endmacro()
