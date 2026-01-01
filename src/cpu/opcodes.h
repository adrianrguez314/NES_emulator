#ifndef opcodes_h
#define opcodes_h

#include <cstdint>

enum Opcodes: uint8_t {
    NOP = 0xEA, // No Operation

    // LDA - Load Accumulator
    LDA_IMM = 0XA9,
    LDA_ZP = 0xA5,
    LDA_ZPX = 0xB5,
    LDA_ABS = 0xAD,
    LDA_ABSX = 0xBD,
    LDA_ABSY = 0xB9,
    LDA_INX = 0xA1,
    LDA_INY = 0xB1,

    //LDX - Load X Register
    LDX_IMM = 0xA2,
    LDX_ZP = 0xA6,
    LDX_ZPY = 0xB6,
    LDX_ABS = 0xAE,
    LDX_ABSY = 0XBE,

    //LDY - Load Y Register
    LDY_IMM = 0xA0,
    LDY_ZP = 0xA4,
    LDY_XZP = 0xB4,
    LDY_ABS = 0xAC,
    LDY_ABSX = 0xBC,
    

};

#endif // opcodes_h