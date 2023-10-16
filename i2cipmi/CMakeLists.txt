SET ( TARGET "${CMAKE_CURRENT_SOURCE_DIR}/target" )
LIST ( APPEND CMAKE_MODULE_PATH "${TARGET}" )

MESSAGE ( STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

INCLUDE (bmc_amd_build)





cmake_minimum_required (VERSION 2.6)
project (i2cipmi)
# The version number.
set (i2cipmi_VERSION_MAJOR 1)
set (i2cipmi_VERSION_MINOR 0)

# add the executable
add_executable (i2cipmi i2cipmi.c)

install(TARGETS i2cipmi
        RUNTIME DESTINATION bin)
