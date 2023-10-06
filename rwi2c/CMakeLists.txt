SET ( TARGET "${CMAKE_CURRENT_SOURCE_DIR}/target" )
LIST ( APPEND CMAKE_MODULE_PATH "${TARGET}" )

MESSAGE ( STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

INCLUDE (bmc_amd_build)





cmake_minimum_required (VERSION 2.6)
project (rwi2c)
# The version number.
set (rwi2c_VERSION_MAJOR 1)
set (rwi2c_VERSION_MINOR 0)

# add the executable
add_executable (rwi2c rwi2c.c)

install(TARGETS rwi2c
        RUNTIME DESTINATION bin)
