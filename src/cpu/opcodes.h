#ifndef opcodes_h
#define opcodes_h

#include <cstdint>
#include "cpu.h" 

enum class Opcode : uint8_t {
    NOP = 0xEA,

    // LDA - Load Accumulator
    LDA_IMM  = 0xA9,
    LDA_ZP   = 0xA5,
    LDA_ZPX  = 0xB5,
    LDA_ABS  = 0xAD,
    LDA_ABSX = 0xBD,
    LDA_ABSY = 0xB9,

    // LDX - Load X
    LDX_IMM  = 0xA2,
    LDX_ZP   = 0xA6,
    LDX_ZPY  = 0xB6,
    LDX_ABS  = 0xAE,
    LDX_ABSY = 0xBE,

    // LDY - Load Y
    LDY_IMM  = 0xA0,
    LDY_ZP   = 0xA4,
    LDY_ZPX  = 0xB4,
    LDY_ABS  = 0xAC,
    LDY_ABSX = 0xBC,
};

struct Instruction {
    CPU::AddressingMode mode;
    uint8_t len;
    uint8_t cycles;
    void (CPU::*handler)(CPU::AddressingMode);
};


static Instruction OPCODE_TABLE[256] = { };

inline void initOpcodeTable() {

    for (int i = 0; i < 256; i++) {
        OPCODE_TABLE[i] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opNOP };
    }

    // LDA
    OPCODE_TABLE[0xA9] = { CPU::AddressingMode::Immediate,  2, 2, &CPU::opLDA };
    OPCODE_TABLE[0xA5] = { CPU::AddressingMode::ZeroPage,   2, 3, &CPU::opLDA };
    OPCODE_TABLE[0xB5] = { CPU::AddressingMode::ZeroPage_X, 2, 4, &CPU::opLDA };
    OPCODE_TABLE[0xAD] = { CPU::AddressingMode::Absolute,   3, 4, &CPU::opLDA };
    OPCODE_TABLE[0xBD] = { CPU::AddressingMode::Absolute_X, 3, 4, &CPU::opLDA };
    OPCODE_TABLE[0xB9] = { CPU::AddressingMode::Absolute_Y, 3, 4, &CPU::opLDA };

    // LDX
    OPCODE_TABLE[0xA2] = { CPU::AddressingMode::Immediate,  2, 2, &CPU::opLDX };
    OPCODE_TABLE[0xA6] = { CPU::AddressingMode::ZeroPage,   2, 3, &CPU::opLDX };
    OPCODE_TABLE[0xB6] = { CPU::AddressingMode::ZeroPage_Y, 2, 4, &CPU::opLDX };
    OPCODE_TABLE[0xAE] = { CPU::AddressingMode::Absolute,   3, 4, &CPU::opLDX };
    OPCODE_TABLE[0xBE] = { CPU::AddressingMode::Absolute_Y, 3, 4, &CPU::opLDX };

    // LDY
    OPCODE_TABLE[0xA0] = { CPU::AddressingMode::Immediate,  2, 2, &CPU::opLDY };
    OPCODE_TABLE[0xA4] = { CPU::AddressingMode::ZeroPage,   2, 3, &CPU::opLDY };
    OPCODE_TABLE[0xB4] = { CPU::AddressingMode::ZeroPage_X, 2, 4, &CPU::opLDY };
    OPCODE_TABLE[0xAC] = { CPU::AddressingMode::Absolute,   3, 4, &CPU::opLDY };
    OPCODE_TABLE[0xBC] = { CPU::AddressingMode::Absolute_X, 3, 4, &CPU::opLDY };
}


#endif // opcodes_h