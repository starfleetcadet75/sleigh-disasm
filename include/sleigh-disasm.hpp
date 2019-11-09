#pragma once

#include "loadimage.hh"
#include "sleigh.hh"
#include "emulate.hh"
#include <iostream>


class AssemblyRaw : public AssemblyEmit {
public:
    virtual void dump(const Address &address, const string &mnemonic, const string &body) {
        address.printRaw(std::cout);
        std::cout << ": " << mnemonic << ' ' << body << endl;
    }
};


class DefaultLoadImage: public LoadImage {
public:
    DefaultLoadImage(uint64_t start_address, const uint8_t *buffer, size_t buffer_size): LoadImage("nofile") {
        this->start_address = start_address;
        this->buffer = buffer;
        this->buffer_size = buffer_size;
    }
  
    virtual void loadFill(uint1 *ptr, int4 size, const Address &address) {
        auto start = address.getOffset();
        auto max = this->start_address + (this->buffer_size - 1);
  
        for (auto i = 0; i < size; i++) {
            auto current_offset = start + i;
            if ((current_offset < this->start_address) || (max < current_offset)) {
            ptr[i] = 0;
            continue;
            }
            auto diff = current_offset - this->start_address;
            ptr[i] = this->buffer[diff];
        }
    }
  
    virtual string getArchType(void) const {
        return "defaultloadimage";
    }
  
    virtual void adjustVma(long adjust) {}

private:
    uint64_t start_address;
    const uint8_t *buffer;
    size_t buffer_size;
};


class SleighDisasm {
public:
    SleighDisasm();
    void configure(const std::string arch);
    void disassemble(const uint8_t *buffer, size_t buffer_size, uint64_t start_address, size_t count);

private:
    ContextInternal context;
    DocumentStorage docstorage;
};
