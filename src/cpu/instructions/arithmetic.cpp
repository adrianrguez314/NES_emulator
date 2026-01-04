#include "../cpu.h"

void CPU::opADC (AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.A += value;
}

void CPU::opSBC (AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.A -= value;
}

void CPU::opINC (AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    mem.write(addr,value++);
}

void CPU::opINX (AddressingMode mode) {
    registers.X++;
}

void CPU::opINY (AddressingMode mode) {
    registers.Y++;
}

void CPU::opDEC (AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    mem.write(addr,value--);
}

void CPU::opDEX (AddressingMode mode) {
    registers.X++;
}

void CPU::opDEY (AddressingMode mode) {
    registers.Y++;
}

