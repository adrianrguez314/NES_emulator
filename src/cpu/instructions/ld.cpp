#include "../cpu.h"

#include <iostream>

void CPU::opLDA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.A = value;
}