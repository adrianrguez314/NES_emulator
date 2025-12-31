#include <iostream>

#include "instructions.h"

void NOP() { }

uint8_t LDA_IMM(Memory& mem,uint8_t addr) {
    return mem.read(addr);
}