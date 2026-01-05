#include "../cpu.h"
#include "../flags.h"

void CPU::opJMP(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    registers.PC = addr;

}

void CPU::opJSR(AddressingMode mode) {
    uint16_t target = getAddress(mode);

    uint16_t returnAddr = registers.PC + 1;

    pushStack((returnAddr >> 8) & 0xFF);
    pushStack(returnAddr & 0xFF);

    registers.PC = target;
}

void CPU::opRTS(AddressingMode mode) {

}

void CPU::opBRK(AddressingMode mode) {

}

void CPU::opRTI(AddressingMode mode) {

}