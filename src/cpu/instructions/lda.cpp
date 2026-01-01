#include "../cpu.h"

#include <iostream>

void CPU::opLDA_IMM() {
    uint8_t value = mem.read(registers.PC + 1);
    registers.A = value;
}