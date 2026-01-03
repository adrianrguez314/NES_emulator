#include "../cpu.h"

void CPU::opLDA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.A = value;
}

void CPU::opLDX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.X = value;

}

void CPU::opLDY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    registers.Y = value;
}