#include <iostream>

#include "cpu.h"
#include "opcodes.h"


CPU::CPU(Memory& memory) : mem(memory) {
    initOpcodeTable();
    reset();
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
    registers.SP = 0xFF;
    registers.status = 0x24;
}

void CPU::pushStack (uint8_t value) {
    mem.write(0x0100 + registers.SP, value);
    registers.SP--;
}

uint8_t CPU::pullStack() {
    registers.SP++;  
    return mem.read(0x0100 + registers.SP);
}

void CPU::executeInstruction() {
    uint8_t opcode = mem.read(registers.PC);
    registers.PC++;
    uint16_t pc_status = registers.PC;
    
    const Instruction& instr = OPCODE_TABLE[opcode];
    (this->*instr.handler)(instr.mode);

    if (registers.PC == pc_status)  
        registers.PC += instr.len - 1; 
}

uint8_t CPU::getRegister(char registerName) const {
    switch (registerName) {
        case 'A':
            return registers.A;
        case 'X':
            return registers.X;
        case 'Y': 
            return registers.Y;
        case 'S':
            return registers.SP;
        default:
            throw std:: invalid_argument("Invalid CPU register");
    }
}

