#ifndef cpu_h
#define cpu_h 

#include <cstdint>
#include <array>

#include "../memory/memory.h"

class CPU {

    Memory& mem;

    public:
        CPU(Memory& memory);
        ~CPU();
        void reset();
        void executeInstruction();

        protected:
            struct Registers {
                uint8_t A;      // Accumulator
                uint8_t X;      // X Register
                uint8_t Y;      // Y Register
                uint16_t PC;     // Program Counter
                uint8_t status; // Status Register
            } registers;
        
            void opLDA_IMM();
            void opSTA_ZP();
            void opNOP();

        private:
            using Opfunc = void(*)(CPU&);
            std::array<Opfunc, 256> opcodeTable;

};
#endif // cpu_h



