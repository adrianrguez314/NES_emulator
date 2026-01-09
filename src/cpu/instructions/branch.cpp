#include "../cpu.h"
#include "../flags.h"


void CPU::opBPL(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (!registers.P.isSet(Flags::NEGATIVE)) registers.PC = addr;
}

void CPU::opBMI(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (registers.P.isSet(Flags::NEGATIVE)) registers.PC = addr;
}

void CPU::opBVC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (!registers.P.isSet(Flags::OVERFLOW)) registers.PC = addr;
}

void CPU::opBVS(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (registers.P.isSet(Flags::OVERFLOW)) registers.PC = addr;
}

void CPU::opBCC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (!registers.P.isSet(Flags::CARRY)) registers.PC = addr;
}

void CPU::opBCS(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (registers.P.isSet(Flags::CARRY)) registers.PC = addr;
}

void CPU::opBNE(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (!registers.P.isSet(Flags::ZERO)) registers.PC = addr;
}

void CPU::opBEQ(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    if (registers.P.isSet(Flags::ZERO)) registers.PC = addr;
}