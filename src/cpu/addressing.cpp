#include <iostream>

#include "cpu.h"


uint16_t CPU::getAddress(AddressingMode mode) {
    switch (mode) {
        case AddressingMode::Immediate:
            registers.PC++;
            return registers.PC;
        case AddressingMode::ZeroPage:
            return 0;
        case AddressingMode::ZeroPage_X:
            return 0;
        case AddressingMode::ZeroPage_Y:
            return 0;
        case AddressingMode::Absolute:
            return 0;
        case AddressingMode::Absolute_X:
            return 0;
        case AddressingMode::Absolute_Y:
            return 0;
        case AddressingMode::Indirect_X:
            return 0;
        case AddressingMode::Indirect_Y:
            return 0;
        default:
            throw std::runtime_error("Addressing mode not implemented");
        
    }
}