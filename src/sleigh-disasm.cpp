#include "sleigh-disasm.hpp"

SleighDisasm::SleighDisasm() {}

void SleighDisasm::configure(const std::string arch) {
    // Read sleigh file into DOM
    Element *sleighroot = docstorage.openDocument(arch)->getRoot();
    docstorage.registerTag(sleighroot);
}
    
void SleighDisasm::disassemble(const uint8_t *buffer, size_t buffer_size, uint64_t start_address, size_t count) {
    DefaultLoadImage loader(start_address, buffer, buffer_size);

    Sleigh translator(&loader, &this->context);
    translator.initialize(docstorage);

    // Now that context symbol names are loaded by the translator we can set the default context
    context.setVariableDefault("addrsize", 1); // Address size is 32-bit
    context.setVariableDefault("opsize", 1); // Operand size is 32-bit

    AssemblyRaw assembly_emitter;
    auto length = 0;  // Number of bytes of each machine instruction

    Address address(translator.getDefaultSpace(), start_address);

    for (auto i = 0; i < count; i++) {
        length = translator.printAssembly(assembly_emitter, address);
        address = address + length;
    }
}
