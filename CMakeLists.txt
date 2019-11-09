cmake_minimum_required(VERSION 3.12)
project(sleigh-disasm)

set(CMAKE_CXX_STANDARD 11)
set(SLEIGH_DISASM_LIBNAME sleigh-disasm)
set(BUILD_SLASPECS ON CACHE STRING "Compile all slaspecs found in the Ghidra submodule")

add_subdirectory(${CMAKE_SOURCE_DIR}/ghidra)

set(SOURCE src/sleigh-disasm.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${SLEIGH_DISASM_LIBNAME} SHARED ${SOURCE})
target_link_libraries(${SLEIGH_DISASM_LIBNAME} ghidra_decompiler_sleigh ghidra_decompiler_base)
set_target_properties(${SLEIGH_DISASM_LIBNAME} PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/sleigh-disasm.hpp")

if(BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples)
endif()

install(TARGETS ${SLEIGH_DISASM_LIBNAME} ghidra_decompiler_sleigh ghidra_decompiler_base
        LIBRARY DESTINATION "lib"
        PUBLIC_HEADER DESTINATION "include"
)