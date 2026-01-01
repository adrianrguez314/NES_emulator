#include <iostream>

#include "cpu.h"
#include "opcodes.h"


CPU::CPU(Memory& memory) : mem(memory) {
    reset();
    initOpcodeTable();
    std::cout << "CPU initialized.\n";
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

void CPU::initOpcodeTable() {
    opcodeTable.fill(&CPU::opNOP);

    opcodeTable[LDA_IMM] = &CPU::opLDA_IMM;
    opcodeTable[NOP]     = &CPU::opNOP;
}

void CPU::executeInstruction() {
    uint8_t opcode = mem.read(registers.PC);

    (this->*opcodeTable[opcode])();
}

uint8_t CPU::getRegister(char registerName) const {
    switch (registerName) {
        case 'A':
            return registers.A;
        case 'X':
            return registers.X;
        case 'Y': 
            return registers.Y;
        default:
            throw std:: invalid_argument("Invalid CPU register");
    }
}

