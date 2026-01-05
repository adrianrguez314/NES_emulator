#ifndef cpu_h
#define cpu_h 

#include <cstdint>
#include <functional>

#include "../memory/memory.h"
#include "flags.h"

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
            Indirect,
            Indirect_X,
            Indirect_Y,
            Not_addressing,
        };
        uint16_t getAddress(AddressingMode mode);

        void setA(uint8_t v) { registers.A = v; }
        void setX(uint8_t v) { registers.X = v; }
        void setY(uint8_t v) { registers.Y = v; }
        void setSP(uint8_t v) { registers.SP = v; }
        uint8_t getRegister(char registerName) const;

        void setPC(uint16_t v) { registers.PC = v; }
        uint16_t getPC() { return registers.PC; }

        void pushStack(uint8_t value);
        uint8_t pullStack();

        Flags& getFlags() { return registers.P; }
        const Flags& getFlags() const { return registers.P; }


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
        void opTXA(AddressingMode mode);
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

        // Compare
        void opCMP(AddressingMode mode);
        void opCPX(AddressingMode mode);
        void opCPY(AddressingMode mode);

        // Jump
        void opJMP(AddressingMode mode);
        void opJSR(AddressingMode mode);
        void opRTS(AddressingMode mode);
        void opBRK(AddressingMode mode);
        void opRTI(AddressingMode mode);

        // Flags
        void opCLC (AddressingMode mode);
        void opCLD(AddressingMode mode);
        void opCLI (AddressingMode mode);
        void opCLV (AddressingMode mode);
        void opSEC (AddressingMode mode);
        void opSED (AddressingMode mode);
        void opSEI (AddressingMode mode);

        // Stack
        void opPHA (AddressingMode mode);
        void opPLA (AddressingMode mode);
        void opPHP (AddressingMode mode);
        void opPLP (AddressingMode mode);
        void opTXS(AddressingMode mode);
        void opTSX(AddressingMode mode);
            
        void opNOP(AddressingMode mode);

        protected:
            struct Registers {
                uint8_t A;      // Accumulator
                uint8_t X;      // X Register
                uint8_t Y;      // Y Register
                uint16_t PC;     // Program Counter
                uint8_t SP;     // Stack Pointer
                uint8_t status; // Status Register

                Flags P;
            } registers;

};
#endif // cpu_h



