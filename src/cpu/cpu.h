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
            };
        uint16_t getAddress(AddressingMode mode);
        uint8_t getRegister(char registerName) const; 

        protected:
            struct Registers {
                uint8_t A;      // Accumulator
                uint8_t X;      // X Register
                uint8_t Y;      // Y Register
                uint16_t PC;     // Program Counter
                uint8_t status; // Status Register
            } registers;
  
            void opLDA(AddressingMode mode);
            void opLDX(AddressingMode mode);
            void opLDY(AddressingMode mode);

            
            void opNOP();

        private:
            std::array<std::function<void(CPU&)>, 256> opcodeTable;
            void initOpcodeTable();

};
#endif // cpu_h



