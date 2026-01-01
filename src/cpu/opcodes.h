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
};

#endif // opcodes_h