#ifndef cpu_h
#define cpu_h 

#include <cstdint>
#include <functional>

#include "../memory/memory.h"

class CPU {

    Memory& mem;

    public:
        CPU(Memory& memory);
        ~CPU();
        void reset();
        void executeInstruction();

        enum class AddressingMode {
            Immediate,
            ZeroPage,
            ZeroPage_X,
            ZeroPage_Y,
            Absolute,
            Absolute_X,
            Absolute_Y,
            Indirect_X,
            Indirect_Y,
            Not_addressing,
            };
        uint16_t getAddress(AddressingMode mode);
        uint8_t getRegister(char registerName) const; 


        // Load Register
        void opLDA(AddressingMode mode);
        void opLDX(AddressingMode mode);
        void opLDY(AddressingMode mode);

        // Store Register
        void opSTA(AddressingMode mode);
        void opSTX(AddressingMode mode);
        void opSTY(AddressingMode mode);

        //Transfers
        void opTAX(AddressingMode mode);
        void opTAY(AddressingMode mode);
        void opTSX(AddressingMode mode);
        void opTXA(AddressingMode mode);
        void opTXS(AddressingMode mode);
        void opTYA(AddressingMode mode);

        // Arithmetic
        void opADC(AddressingMode mode);
        void opSBC(AddressingMode mode);
        void opINC(AddressingMode mode);
        void opDEC(AddressingMode mode);

        // Register increments
        void opINX(AddressingMode mode);
        void opDEX(AddressingMode mode);
        void opINY(AddressingMode mode);
        void opDEY(AddressingMode mode);
            
        void opNOP(AddressingMode mode);

        protected:
            struct Registers {
                uint8_t A;      // Accumulator
                uint8_t X;      // X Register
                uint8_t Y;      // Y Register
                uint16_t PC;     // Program Counter
                uint8_t status; // Status Register
            } registers;

};
#endif // cpu_h



