#include "../cpu.h"

void CPU::opTAX (AddressingMode mode) {
    registers.X = registers.A;
}

void CPU::opTAY(AddressingMode mode) {
    registers.Y = registers.A;
}

void CPU::opTSX (AddressingMode mode) {
    throw "Not implemented";
}

void CPU::opTXA (AddressingMode mode) {
    registers.A = registers.X;
}

void CPU::opTXS (AddressingMode mode) {
    throw "Not implemented";
}

void CPU::opTYA (AddressingMode mode) {
    registers.A = registers.Y;
}

