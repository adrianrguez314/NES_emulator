#ifndef opcodes_h
#define opcodes_h

#include <cstdint>
#include "cpu.h" 

enum class Opcode : uint8_t {
    NOP = 0xEA,

    // =========================
    // Load Instructions
    // =========================

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

    // =========================
    // Store Instructions
    // =========================

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

    // =========================
    // Transfer Instructions
    // =========================

    TAX = 0xAA,
    TAY = 0xA8,
    TSX = 0xBA,
    TXA = 0x8A,
    TXS = 0x9A,
    TYA = 0x98,

    // =========================
    // Arithmetic Instructions
    // =========================

    // ADC (Add with Carry)
    ADC_IMM  = 0x69,
    ADC_ZP   = 0x65,
    ADC_ZPX  = 0x75,
    ADC_ABS  = 0x6D,
    ADC_ABSX = 0x7D,
    ADC_ABSY = 0x79,
    ADC_INX  = 0x61,
    ADC_INY  = 0x71,

    // SBC (Subtract with Carry)
    SBC_IMM  = 0xE9,
    SBC_ZP   = 0xE5,
    SBC_ZPX  = 0xF5,
    SBC_ABS  = 0xED,
    SBC_ABSX = 0xFD,
    SBC_ABSY = 0xF9,
    SBC_INX  = 0xE1,
    SBC_INY  = 0xF1,

    // INC (Increment Memory)
    INC_ZP   = 0xE6,
    INC_ZPX  = 0xF6,
    INC_ABS  = 0xEE,
    INC_ABSX = 0xFE,

    // DEC (Decrement Memory)
    DEC_ZP   = 0xC6,
    DEC_ZPX  = 0xD6,
    DEC_ABS  = 0xCE,
    DEC_ABSX = 0xDE,

    // INX / DEX / INY / DEY (Implied)
    INX = 0xE8,
    DEX = 0xCA,
    INY = 0xC8,
    DEY = 0x88,

    // =========================
    // Flags Instructions
    // =========================

    CLC = 0x18,
    CLD = 0xD8,
    CLI = 0x58,
    CLV = 0xB8,
    SEC = 0x38,
    SED = 0xF8,
    SEI = 0x78,


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

    // TRANSFER instructions
    OPCODE_TABLE[0xAA] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTAX };
    OPCODE_TABLE[0xA8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTAY };
    OPCODE_TABLE[0xBA] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTSX };
    OPCODE_TABLE[0x8A] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTXA };
    OPCODE_TABLE[0x9A] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTXS };
    OPCODE_TABLE[0x98] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opTYA };

    // ADC 
    OPCODE_TABLE[0x69] = { CPU::AddressingMode::Immediate,  2, 2, &CPU::opADC };
    OPCODE_TABLE[0x65] = { CPU::AddressingMode::ZeroPage,   2, 3, &CPU::opADC };
    OPCODE_TABLE[0x75] = { CPU::AddressingMode::ZeroPage_X, 2, 4, &CPU::opADC };
    OPCODE_TABLE[0x6D] = { CPU::AddressingMode::Absolute,   3, 4, &CPU::opADC };
    OPCODE_TABLE[0x7D] = { CPU::AddressingMode::Absolute_X, 3, 4, &CPU::opADC };
    OPCODE_TABLE[0x79] = { CPU::AddressingMode::Absolute_Y, 3, 4, &CPU::opADC };
    OPCODE_TABLE[0x61] = { CPU::AddressingMode::Indirect_X, 2, 6, &CPU::opADC };
    OPCODE_TABLE[0x71] = { CPU::AddressingMode::Indirect_Y, 2, 5, &CPU::opADC };

    // SBC 
    OPCODE_TABLE[0xE9] = { CPU::AddressingMode::Immediate,  2, 2, &CPU::opSBC };
    OPCODE_TABLE[0xE5] = { CPU::AddressingMode::ZeroPage,   2, 3, &CPU::opSBC };
    OPCODE_TABLE[0xF5] = { CPU::AddressingMode::ZeroPage_X, 2, 4, &CPU::opSBC };
    OPCODE_TABLE[0xED] = { CPU::AddressingMode::Absolute,   3, 4, &CPU::opSBC };
    OPCODE_TABLE[0xFD] = { CPU::AddressingMode::Absolute_X, 3, 4, &CPU::opSBC };
    OPCODE_TABLE[0xF9] = { CPU::AddressingMode::Absolute_Y, 3, 4, &CPU::opSBC };
    OPCODE_TABLE[0xE1] = { CPU::AddressingMode::Indirect_X, 2, 6, &CPU::opSBC };
    OPCODE_TABLE[0xF1] = { CPU::AddressingMode::Indirect_Y, 2, 5, &CPU::opSBC };

    // INC 
    OPCODE_TABLE[0xE6] = { CPU::AddressingMode::ZeroPage,   2, 5, &CPU::opINC };
    OPCODE_TABLE[0xF6] = { CPU::AddressingMode::ZeroPage_X, 2, 6, &CPU::opINC };
    OPCODE_TABLE[0xEE] = { CPU::AddressingMode::Absolute,   3, 6, &CPU::opINC };
    OPCODE_TABLE[0xFE] = { CPU::AddressingMode::Absolute_X, 3, 7, &CPU::opINC };

    // DEC 
    OPCODE_TABLE[0xC6] = { CPU::AddressingMode::ZeroPage,   2, 5, &CPU::opDEC };
    OPCODE_TABLE[0xD6] = { CPU::AddressingMode::ZeroPage_X, 2, 6, &CPU::opDEC };
    OPCODE_TABLE[0xCE] = { CPU::AddressingMode::Absolute,   3, 6, &CPU::opDEC };
    OPCODE_TABLE[0xDE] = {CPU::AddressingMode::Absolute_X, 3, 7, &CPU::opDEC };

    // Register increments (Implied)
    OPCODE_TABLE[0xE8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opINX };
    OPCODE_TABLE[0xCA] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opDEX };
    OPCODE_TABLE[0xC8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opINY };
    OPCODE_TABLE[0x88] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opDEY };

    // Flags instructions
    OPCODE_TABLE[0x18] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opCLC };
    OPCODE_TABLE[0xD8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opCLD };
    OPCODE_TABLE[0x58] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opCLI };
    OPCODE_TABLE[0xB8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opCLV };
    OPCODE_TABLE[0x38] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opSEC };
    OPCODE_TABLE[0xF8] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opSED };
    OPCODE_TABLE[0x78] = { CPU::AddressingMode::Not_addressing, 1, 2, &CPU::opSEI };
}

#endif // opcodes_h