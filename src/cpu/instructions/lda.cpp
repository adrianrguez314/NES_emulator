#include "../cpu.h"

void CPU::opLDA_IMM() {

    uint8_t value = mem.read(registers.PC++);
    registers.A = value;
}