cmake_minimum_required(VERSION 3.12)
project(sleigh-disasm VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(SLEIGH_DISASM_LIBRARY sleigh-disasm)
set(BUILD_SLASPECS ON CACHE STRING "Compile all slaspecs found in the Ghidra submodule")

add_subdirectory(${CMAKE_SOURCE_DIR}/ghidra)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${SLEIGH_DISASM_LIBRARY} SHARED src/sleigh-disasm.cpp)
target_link_libraries(${SLEIGH_DISASM_LIBRARY} ${SLEIGH_LIBRARY})
set_target_properties(${SLEIGH_DISASM_LIBRARY} PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/sleigh-disasm.hpp")

if(BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples)
endif()

install(TARGETS ${SLEIGH_DISASM_LIBRARY}
        LIBRARY DESTINATION "lib"
        PUBLIC_HEADER DESTINATION "include"
)
