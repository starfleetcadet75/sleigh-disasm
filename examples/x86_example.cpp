#include <sleigh-disasm.hpp>

static uint8_t code[] = {
    0x55, 0x48, 0x8b, 0x05, 0xb8, 0x13, 0x00, 0x00
};

int main(int argc, char **argv) {
    std::string sleigh_filename = "ghidra/specfiles/x86.sla";
    SleighDisasm handle;

    // Provide the path to the compiled sla file to use
    handle.configure(sleigh_filename);

    // Disassemble 8 instructions from the code buffer starting at address 0x1000
    handle.disassemble(code, sizeof(code) - 1, 0x1000, 8);
    return 0;
}
