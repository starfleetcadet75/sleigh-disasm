set(EXAMPLE_SOURCE x86_example.cpp)

add_executable(x86_example ${EXAMPLE_SOURCE})

target_link_libraries(x86_example ${SLEIGH_DISASM_LIBNAME})