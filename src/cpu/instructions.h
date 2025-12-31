#ifndef instructions_h
#define instructions_h

#include <cstdint>

#include "../memory/memory.h"

void NOP();
uint8_t LDA_IMM(Memory& memory,uint8_t value); 


#endif // instrucitions_h