# sleigh-disasm
> Simple architecture-agnostic disassembly library using SLEIGH

## About
[Ghidra](https://github.com/NationalSecurityAgency/ghidra) uses the [SLEIGH language](https://ghidra.re/courses/languages/html/sleigh.html) for rapidly creating support for different processors.
`sleigh-disasm` is a C++ wrapper around some of the SLEIGH parsing code used by the Ghidra decompiler.
It provides a simple disassembly API, similar to [Capstone](https://github.com/aquynh/capstone), that can support any architecture given a compiled slaspec file.

## Example
```c++
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
```

#### Output
```
0x00001000: PUSH EBP
0x00001001: DEC EAX
0x00001002: MOV EAX,dword ptr [0x13b8]
0x00001008: ADD byte ptr [EAX],AL
0x0000100a: ADD byte ptr [EAX],AL
0x0000100c: ADD byte ptr [EAX],AL
0x0000100e: ADD byte ptr [EAX],AL
0x00001010: ADD byte ptr [EAX],AL
```

## Compiling
Update the Ghidra submodule to pull the latest sources to build against:
```bash
git submodule init
git submodule update
```

Run the CMake build:
```bash
mkdir build && cd build
cmake -DBUILD_EXAMPLES=ON ..
make
make install
```

By default, CMake will build the SLEIGH compiler executable and then use it to build all of the slaspecs that are found in the Ghidra submodule.
If you do not wish to build all of the slaspecs at once, you can disable this by passing BUILD_SLASPECS=OFF to CMake.

## Contributing
All contributions are welcome.
