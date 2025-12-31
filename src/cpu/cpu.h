#ifndef cpu_h
#define cpu_h 
#include <cstdint>

#include "../memory/memory.h"

class CPU {

    Memory& mem;

    public:
        CPU(Memory& memory);
        ~CPU();
        void reset();
        void executeInstruction();
        
        private:
        struct Register {
            uint8_t A;
            uint8_t X;
            uint8_t Y;
            uint8_t PC;
            uint8_t status;
        } registers;
};
#endif // cpu_h



