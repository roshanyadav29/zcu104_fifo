# Copyright (C) 2023 - 2025 Advanced Micro Devices, Inc.  All rights reserved.
# SPDX-License-Identifier: MIT
set( CMAKE_EXPORT_COMPILE_COMMANDS ON)
set( CMAKE_INSTALL_MESSAGE LAZY)
set( CMAKE_SYSTEM_PROCESSOR "cortexa53" )
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "cortexa53")
set( CMAKE_C_COMPILER aarch64-none-elf-gcc )
set( CMAKE_CXX_COMPILER aarch64-none-elf-g++ )
set( CMAKE_ASM_COMPILER aarch64-none-elf-gcc )
set( CMAKE_AR aarch64-none-elf-ar CACHE FILEPATH "Archiver" )
set( CMAKE_SIZE aarch64-none-elf-size CACHE FILEPATH "Size" )
elseif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "cortexa53-32")
set( CMAKE_C_COMPILER arm-none-eabi-gcc )
set( CMAKE_CXX_COMPILER arm-none-eabi-g++ )
set( CMAKE_ASM_COMPILER arm-none-eabi-gcc )
set( CMAKE_AR arm-none-eabi-ar CACHE FILEPATH "Archiver" )
set( CMAKE_SIZE arm-none-eabi-size CACHE FILEPATH "Size" )
endif()
set( CMAKE_C_COMPILER_LAUNCHER  )
set( CMAKE_CXX_COMPILER_LAUNCHER  )
set( CMAKE_MACHINE "ZynqMP" )
set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SPECS_FILE "$ENV{ESW_REPO}/scripts/specs/arm/Xilinx.spec" CACHE STRING "Specs file path for using CMAKE toolchain files" )
set( TOOLCHAIN_C_FLAGS " -DSDT" CACHE STRING "CFLAGS" )
set( TOOLCHAIN_CXX_FLAGS " -DSDT" CACHE STRING "CXXFLAGS" )
set( TOOLCHAIN_ASM_FLAGS " -DSDT" CACHE STRING "ASM FLAGS" )
set( TOOLCHAIN_DEP_FLAGS " -MMD -MP" CACHE STRING "Flags used by compiler to generate dependency files")
set( TOOLCHAIN_EXTRA_C_FLAGS " -O2 -g -Wall -Wextra -fno-tree-loop-distribute-patterns" CACHE STRING "Extra CFLAGS")
set( CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CFLAGS for release" )
set( CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CXXFLAGS for release" )
set( CMAKE_ASM_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional ASM FLAGS for release" )
set( CMAKE_C_FLAGS "${TOOLCHAIN_C_FLAGS} ${TOOLCHAIN_DEP_FLAGS} -specs=${CMAKE_SPECS_FILE} -I${CMAKE_INCLUDE_PATH}" CACHE STRING "CFLAGS")
set( CMAKE_CXX_FLAGS "${TOOLCHAIN_CXX_FLAGS} ${TOOLCHAIN_DEP_FLAGS} -specs=${CMAKE_SPECS_FILE} -I${CMAKE_INCLUDE_PATH}" CACHE STRING "CXXFLAGS")
set( CMAKE_ASM_FLAGS "${TOOLCHAIN_ASM_FLAGS} ${TOOLCHAIN_DEP_FLAGS} -specs=${CMAKE_SPECS_FILE} -I${CMAKE_INCLUDE_PATH}" CACHE STRING "ASMFLAGS")
set(TEMPLATE "empty_application")
set( CMAKE_HOST_NAME Windows)
