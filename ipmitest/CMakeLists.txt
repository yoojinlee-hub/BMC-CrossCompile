SET ( TARGET "${CMAKE_CURRENT_SOURCE_DIR}/target" )
LIST ( APPEND CMAKE_MODULE_PATH "${TARGET}" )

MESSAGE ( STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

INCLUDE (bmc_amd_build)





cmake_minimum_required (VERSION 2.6)
project (ipmitest)
# The version number.
set (ipmitest_VERSION_MAJOR 1)
set (ipmitest_VERSION_MINOR 0)

# add the executable
add_executable (ipmitest ipmitest.c)

install(TARGETS ipmitest
        RUNTIME DESTINATION bin)
