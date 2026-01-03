#include "../cpu.h"

#include <iostream>

void CPU::opLDA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.A = value;
    registers.PC++;
}

void CPU::opLDX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.X = value;
    registers.PC++;
}

void CPU::opLDY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.Y = value;
    registers.PC++;
}