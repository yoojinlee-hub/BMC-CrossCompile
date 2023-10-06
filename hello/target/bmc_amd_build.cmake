# Define our host system
SET ( CMAKE_SYSTEM_NAME Linux )
SET ( CMAKE_SYSTEM_PROCESSOR aarch64 )
SET ( CMAKE_CROSSCOMPILING 1 )
SET ( CMAKE_SYSTEM_VERSION 1 )

# SET ( TOOLCHAIN_ROOT "/home/sikim/opt/toolchains/odroid-c4" )
SET ( TOOLCHAIN_ROOT "/usr/local/oecore-x86_64" )
SET ( CROSS_PREFIX "arm-openbmc-linux-gnueabi" )


# Define the cross compiler locations
IF ( NOT TOOLCHAIN_ROOT_DIR ) # If the toolchain directory is not passed via command line
#    SET ( TOOLCHAIN_ROOT_DIR "${TOOLCHAIN_ROOT}/gcc-linaro-7.5.0-2019.12-x86_64_${CROSS_PREFIX}/bin" )
    SET ( TOOLCHAIN_ROOT_DIR "/usr/local/oecore-x86_64" )
ENDIF()

MESSAGE ( STATUS "TOOLCHAIN_ROOT_DIR: ${TOOLCHAIN_ROOT_DIR}")

# Check if the cross compiler is installed
IF ( NOT EXISTS "${TOOLCHAIN_ROOT_DIR}" )
    MESSAGE ( FATAL_ERROR "\
 ARM toolchain is not installed.\n\
 On debian based systems it can be installed by the command:\n\
     sudo apt install g{cc,++}-arm-linux-gnueabihf\n\
 Or you can specify its location by specifying it via -DTOOLCHAIN_ROOT_DIR=")
ENDIF()

SET(CMAKE_C_COMPILER "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-gcc")
SET(CMAKE_CXX_COMPILER "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-g++")
SET ( CMAKE_LINKER "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-ld" )
SET ( CMAKE_AR "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-ar" )
SET ( CMAKE_RANLIB "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-ranlib" )
SET ( CMAKE_STRIP "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-strip" )
SET ( CMAKE_NM "/usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-openbmc-linux-gnueabi/arm-openbmc-linux-gnueabi-nm" )

# SET ( TOOLCHAIN_LD "${TOOLCHAIN_ROOT_DIR}/${CROSS_PREFIX}-ld" )
# SET ( TOOLCHAIN_AR "${TOOLCHAIN_ROOT_DIR}/${CROSS_PREFIX}-ar" )
# SET ( TOOLCHAIN_RANLIB "${TOOLCHAIN_ROOT_DIR}/${CROSS_PREFIX}-ranlib" )
# SET ( TOOLCHAIN_STRIP "${TOOLCHAIN_ROOT_DIR}/${CROSS_PREFIX}-strip" )
# SET ( TOOLCHAIN_NM "${TOOLCHAIN_ROOT_DIR}/${CROSS_PREFIX}-nm" )

# Define the sysroot
SET(ROOT_PATH "/usr/local/oecore-x86_64/sysroots/armv7ahf-vfpv4d16-openbmc-linux-gnueabi")
# SET ( ROOT_PATH "${TOOLCHAIN_ROOT}/gcc-linaro-7.5.0-2019.12-x86_64_${CROSS_PREFIX}/${CROSS_PREFIX}/libc" )
# SET ( ROOT_PATH /home/sikim/project/msdtester/tantalus/libs/odroid-c4/rootfs )

IF ( NOT ROOT_PATH ) # If the ROOT_PATH directory is not exist
    MESSAGE (STATUS "NOT FOUND ROOT_PATH")
ENDIF()
MESSAGE (STATUS "ROOT_PATH: ${ROOT_PATH}")

# SET ( ROOT_PATH "${TOOLCHAIN_ROOT}/gcc-linaro-7.5.0-2019.12-x86_64_${CROSS_PREFIX}/${CROSS_PREFIX}" )
SET ( CMAKE_SYSROOT ${ROOT_PATH} )
# SET ( CMAKE_FIND_ROOT_PATH ${ROOT_PATH} ${ROOT_PATH}/lib ${ROOT_PATH}/usr/lib )
# SET ( CMAKE_FIND_ROOT_PATH ${ROOT_PATH}/lib ${ROOT_PATH}/usr/lib /lib /usr/lib )
#list(APPEND CMAKE_FIND_ROOT_PATH
#    ${CMAKE_SYSROOT}/lib
#    ${CMAKE_SYSROOT}/usr/lib
#)
#MESSAGE ( STATUS "Searching for ARM root path in: ${CMAKE_FIND_ROOT_PATH}" )

# 컴파일러 및 링커 플래그 설정
SET(CMAKE_C_FLAGS "--sysroot=${ROOT_PATH}")
SET(CMAKE_CXX_FLAGS "--sysroot=${ROOT_PATH}")
SET(CMAKE_EXE_LINKER_FLAGS "--sysroot=${ROOT_PATH}")
SET(CMAKE_SHARED_LINKER_FLAGS "--sysroot=${ROOT_PATH}")
SET(CMAKE_MODULE_LINKER_FLAGS "--sysroot=${ROOT_PATH}")



# SET(CMAKE_FIND_ROOT_PATH $ENV{ROOTFS_DIR} $ENV{CROSSROOT_DIR})
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --sysroot=${ROOT_PATH}" CACHE STRING "cache it")
# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${ROOT_PATH}" CACHE STRING "cache it")
# SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${ROOT_PATH}" CACHE STRING "cache it")
# SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${ROOT_PATH}" CACHE STRING "cache it")

# Use our definitions for compiler tools
SET ( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )

# Search for libraries and headers in the target directories only
SET ( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
SET ( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
SET ( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

# VFP 레지스터 인자 사용
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard -mfpu=neon")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mfpu=neon")
