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

    auto setInstruction = [&](uint8_t code, CPU::AddressingMode mode, uint8_t len,
                              void (CPU::*func)(CPU::AddressingMode)) { 
        opcodeTable[code] = { code, mode, len, [mode, func](CPU& cpu){ (cpu.*func)(mode); } };
    };

    // Inicializa todo a NOP
    for (size_t i = 0; i < opcodeTable.size(); ++i) setInstruction(i, CPU::AddressingMode::Not_addressing, 1, &CPU::opNOP);

    // LDA
    setInstruction(LDA_IMM, CPU::AddressingMode::Immediate, 2, &CPU::opLDA);
    setInstruction(LDA_ZP, CPU::AddressingMode::ZeroPage, 2, &CPU::opLDA);
    setInstruction(LDA_ZPX, CPU::AddressingMode::ZeroPage_X, 2, &CPU::opLDA);
    setInstruction(LDA_ABS, CPU::AddressingMode::Absolute, 3, &CPU::opLDA);
    setInstruction(LDA_ABSX, CPU::AddressingMode::Absolute_X, 3, &CPU::opLDA);
    setInstruction(LDA_ABSY, CPU::AddressingMode::Absolute_Y, 3, &CPU::opLDA);

    setInstruction(LDX_IMM, CPU::AddressingMode::Immediate, 2, &CPU::opLDX);
    setInstruction(LDX_ZP, CPU::AddressingMode::ZeroPage, 2, &CPU::opLDX);
    setInstruction(LDX_ZPY, CPU::AddressingMode::ZeroPage_Y, 2, &CPU::opLDX);
    setInstruction(LDX_ABS, CPU::AddressingMode::Absolute, 3, &CPU::opLDX);
    setInstruction(LDX_ABSY, CPU::AddressingMode::Absolute_Y, 3, &CPU::opLDX);

    setInstruction(LDY_IMM, CPU::AddressingMode::Immediate, 2, &CPU::opLDY);
    setInstruction(LDY_ZP, CPU::AddressingMode::ZeroPage, 2, &CPU::opLDY);
    setInstruction(LDY_ZPX, CPU::AddressingMode::ZeroPage_X, 2, &CPU::opLDY);
    setInstruction(LDY_ABS, CPU::AddressingMode::Absolute, 3, &CPU::opLDY);
    setInstruction(LDY_ABSX, CPU::AddressingMode::Absolute_X, 3, &CPU::opLDY);

    setInstruction(NOP, CPU::AddressingMode::Not_addressing, 1, &CPU::opNOP);
}


void CPU::executeInstruction() {
    uint8_t opcode = mem.read(registers.PC);
    registers.PC++;
    uint16_t pc_status = registers.PC;

    auto& entry = opcodeTable[opcode];
    entry.exec(*this);  

    if (registers.PC == pc_status)  
        registers.PC += entry.len - 1; 
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

