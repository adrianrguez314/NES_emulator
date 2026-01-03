#include "../cpu.h"


void CPU::opSTA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    mem.write(addr,registers.A);
} 

void CPU::opSTX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    mem.write(addr,registers.X);
} 

void CPU::opSTY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    mem.write(addr,registers.Y);
} 
