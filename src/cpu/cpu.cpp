#include <iostream>

#include "cpu.h"
#include "opcodes.h"
#include "instructions.h"


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
    std::cout << "Executing instrucction at PC: " << static_cast<int>(registers.PC) << "\n";
    uint8_t opcode = mem.read(registers.PC);

    switch (opcode) {
        case Opcodes::NOP:
             NOP();
             registers.PC += 1;
             break;
        case Opcodes::LDA_IMM:
            uint8_t value = mem.read(registers.PC +1);

            registers.A = LDA_IMM(mem, value);
            registers.PC += 2;
            break;
        default: 
            std::cout << "Unknown opcode: " << std::hex << static_cast<int>(opcode) << "\n";
    }
}

