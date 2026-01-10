#include <iostream>
#include <iomanip>

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

int CPU::executeInstruction() {
    uint8_t opcode = mem.read(registers.PC);
    registers.PC++;
    uint16_t pc_status = registers.PC;
    
    const Instruction& instr = OPCODE_TABLE[opcode];
    (this->*instr.handler)(instr.mode);

    if (registers.PC == pc_status)  registers.PC += instr.len - 1; 

    return instr.cycles;
}

void CPU::run(int cycles_to_run) {
    while (cycles_to_run > 0) {
        if (cycles_remaining <= 0) {
            if (debug_enabled) trace();
            int cycles_consumed = executeInstruction();
            cycles_remaining = cycles_consumed;
        }

        cycles_remaining--;
        cycles_to_run--;
        total_cycles++;

    }
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

void CPU::trace() {
    uint8_t debugOpcode = mem.read(registers.PC);
    
    std::cout << std::hex << std::uppercase << std::setfill('0');

    std::cout << std::setw(4) << static_cast<int>(registers.PC) << "  "
              << std::setw(2) << static_cast<int>(debugOpcode) << "        "
              << "A:"  << std::setw(2) << static_cast<int>(registers.A) << " "
              << "X:"  << std::setw(2) << static_cast<int>(registers.X) << " "
              << "Y:"  << std::setw(2) << static_cast<int>(registers.Y) << " "
              << "P:"  << std::setw(2) << static_cast<int>(registers.SP) << " "
              << "SP:" << std::setw(2) << static_cast<int>(registers.status) << " "
              << std::dec << "CYC:" << total_cycles 
              << std::endl;
}

