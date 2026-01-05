#include "../cpu.h"
#include "../flags.h"

void CPU::opJMP(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    registers.PC = addr;

}

void CPU::opJSR(AddressingMode mode) {

}

void CPU::opRTS(AddressingMode mode) {

}

void CPU::opBRK(AddressingMode mode) {

}

void CPU::opRTI(AddressingMode mode) {

}