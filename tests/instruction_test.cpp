#include "../src/cpu/cpu.h"
#include "../src/memory/memory.h"
#include "../src/cpu/opcodes.h"
#include <cassert>
#include <iostream>

void testMemoryReadWrite() {
    Memory mem;
    mem.write(0x0001, 0x30);
    assert(mem.read(0x0001) == 0x30);
    std:: cout << "Test Memory Read/Write passed. \n";
}

void testLDAImm() {
    Memory mem;
    CPU cpu(mem);

    // Load LDA_IMM instruction at address 0
    mem.write(0x0000, LDA_IMM);
    mem.write(0x0001, 0x42);
    cpu.reset();
    std::cout << "Memory: " << std::hex << (int)mem.read(0x0000) << " " << std::hex << (int) mem.read(0x0001) << "\n";
    std::cout << cpu.getRegister('A') << "\n";
    cpu.executeInstruction();
    std::cout << cpu.getRegister('A') << "\n";
    assert(cpu.getRegister('A')  == 0x42);
    std:: cout << "Test LDA_IMM passed. \n";

}

int main() {
    testMemoryReadWrite();
    testLDAImm();

    std::cout << "All CPU/Memory tests passed.\n";
    return 0;
}