#include <iostream>

#include "cpu.h"


uint16_t CPU::getAddress(AddressingMode mode) {
    switch (mode) {
        case AddressingMode::Immediate: 
            return registers.PC; 

        case AddressingMode::ZeroPage: 
            return static_cast<uint16_t> (mem.read(registers.PC));
    
        case AddressingMode::ZeroPage_X: {
            uint8_t pos = mem.read(registers.PC);
            return static_cast<uint16_t>((pos + registers.X) & 0xFF);
        }

        case AddressingMode::ZeroPage_Y: {
            uint8_t pos = mem.read(registers.PC);
            return static_cast<uint16_t>((pos + registers.Y) & 0xFF);
        }

        case AddressingMode::Absolute:
            return mem.read_u16(registers.PC);

        case AddressingMode::Absolute_X: {
            uint16_t pos = mem.read_u16(registers.PC);
            return pos + registers.X;
        }
        
        case AddressingMode::Absolute_Y: {
            uint16_t pos = mem.read_u16(registers.PC);
            return pos + registers.Y;
        }

        case AddressingMode::Indirect_X:
            return 0;

        case AddressingMode::Indirect_Y:
            return 0;
        
        default:
            throw std::runtime_error("Addressing mode not implemented");
    }
}