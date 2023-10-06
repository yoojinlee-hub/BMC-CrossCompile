SET ( TARGET "${CMAKE_CURRENT_SOURCE_DIR}/target" )
LIST ( APPEND CMAKE_MODULE_PATH "${TARGET}" )

MESSAGE ( STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

INCLUDE (bmc_amd_build)





cmake_minimum_required (VERSION 2.6)
project (test)
# The version number.
set (test_VERSION_MAJOR 1)
set (test_VERSION_MINOR 0)

# add the executable
add_executable (test test.c)

install(TARGETS test
        RUNTIME DESTINATION bin)
