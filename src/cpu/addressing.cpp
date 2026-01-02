#include "cpu.h"


uint16_t CPU::getAddress(AddressingMode mode) {
    switch (mode) {
        case AddressingMode::Immediate:
            return 0;
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
        case AddressingMode::NoneAddressing:
            return 0;
        
    }
}