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

        case AddressingMode::Indirect: {
            uint16_t ptr = mem.read_u16(registers.PC);
            registers.PC++;

            uint8_t low  = mem.read(ptr);
            uint8_t high = mem.read((ptr & 0xFF00) | ((ptr + 1) & 0x00FF)); 

            return static_cast<uint16_t>(high) << 8 | low;
        }

        case AddressingMode::Indirect_X: {
            uint8_t base = mem.read(registers.PC);
            registers.PC++;
            
            uint8_t ptr = (base + registers.X) & 0xFF;  

            uint8_t low  = mem.read(ptr);               
            uint8_t high = mem.read((ptr + 1) & 0xFF);  

            return static_cast<uint16_t>(high) << 8 | low;
        }

        case AddressingMode::Indirect_Y: {
            uint8_t base = mem.read(registers.PC);
            registers.PC++; 

            uint8_t low  = mem.read(base);               
            uint8_t high = mem.read((base + 1) % 0xFF);
            
            uint16_t addr = (static_cast<uint16_t>(high) << 8 | low);
            return addr + registers.Y;
        }

        case AddressingMode::Accumulator: {
            return 0;
        }
        
        default:
            throw std::runtime_error("Addressing mode not implemented");
    }
}