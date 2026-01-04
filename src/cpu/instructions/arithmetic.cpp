#include "../cpu.h"
#include "../flags.h"

void CPU::opADC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);

    uint16_t result = registers.A + value + (Flags::isSet(registers.status,Flags::CARRY) ? 1 : 0);
    // Flags::updateCarry(registers.P, result);
    registers.A = static_cast<uint8_t>(result);
}

void CPU::opSBC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);

    uint16_t result = registers.A + (uint8_t)(~value) + (Flags::isSet(registers.status,Flags::CARRY) ? 1 : 0);

    //updateCarry(registers.P, result);
    registers.A = static_cast<uint8_t>(result);
}


void CPU::opINC (AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = mem.read(addr);
    mem.write(addr,value + 1);
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
    mem.write(addr,value - 1);
}

void CPU::opDEX (AddressingMode mode) {
    registers.X--;
}

void CPU::opDEY (AddressingMode mode) {
    registers.Y--;
}

