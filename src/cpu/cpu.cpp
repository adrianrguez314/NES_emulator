#include "cpu.h"
#include "opcodes.h"


CPU::CPU(Memory& memory) : mem(memory) {
    std::cout << "CPU initialized.\n";
    this->reset();
}

CPU::~CPU () {
    std::cout << "CPU destroyed.\n";
}

void CPU::reset() {
    registers.A = 0;
    registers.X = 0;
    registers.Y = 0;
    registers.PC = 0;
    registers.status = 0;
}

void CPU::executeInstruction() {
    uint8_t opcode = mem.read(registers.PC);
    opcodeTable[opcode](*this);

}

