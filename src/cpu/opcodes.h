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
    LDA_INX = 0xA1,
    LDA_INY = 0xB2,

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

    //STA - Store A
    STA_ZP = 0x85,
    STA_ZPX = 0x95,
    STA_ABS = 0x8D,
    STA_ABSX = 0x90,
    STA_ABSY = 0x99,
    STA_INX = 0x81,
    STA_INY = 0x92,

    //STX - Store X
    STX_ZP = 0x86,
    STX_ZPY = 0x96,
    STX_ABS = 0x8E,

    //STY - Store Y
    STY_ZP = 0x84,
    STY_ZPX = 0x94,
    STY_ABS = 0x8C,

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
    OPCODE_TABLE[0xA1] = { CPU::AddressingMode::Indirect_X, 3, 4, &CPU::opLDA };
    OPCODE_TABLE[0xB2] = { CPU::AddressingMode::Indirect_Y, 3, 4, &CPU::opLDA };

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

    // STA
    OPCODE_TABLE[0x85] = { CPU::AddressingMode::ZeroPage,   2, 2, &CPU::opSTA };
    OPCODE_TABLE[0x95] = { CPU::AddressingMode::ZeroPage_X, 2, 3, &CPU::opSTA };
    OPCODE_TABLE[0x8D] = { CPU::AddressingMode::Absolute,   2, 4, &CPU::opSTA };
    OPCODE_TABLE[0x90] = { CPU::AddressingMode::Absolute_X, 3, 4, &CPU::opSTA };
    OPCODE_TABLE[0x99] = { CPU::AddressingMode::Absolute_Y, 3, 4, &CPU::opSTA };
    OPCODE_TABLE[0x81] = { CPU::AddressingMode::Indirect_X, 3, 4, &CPU::opSTA };
    OPCODE_TABLE[0x92] = { CPU::AddressingMode::Indirect_Y, 3, 4, &CPU::opSTA };

    // STX
    OPCODE_TABLE[0x86] = { CPU::AddressingMode::ZeroPage,   2, 2, &CPU::opSTX };
    OPCODE_TABLE[0x96] = { CPU::AddressingMode::ZeroPage_Y, 2, 3, &CPU::opSTX };
    OPCODE_TABLE[0x8E] = { CPU::AddressingMode::Absolute,   2, 4, &CPU::opSTX };

    // STY
    OPCODE_TABLE[0x84] = { CPU::AddressingMode::ZeroPage,   2, 2, &CPU::opSTY };
    OPCODE_TABLE[0x94] = { CPU::AddressingMode::ZeroPage_X, 2, 3, &CPU::opSTY };
    OPCODE_TABLE[0x8C] = { CPU::AddressingMode::Absolute,   2, 4, &CPU::opSTY };
}


#endif // opcodes_h