#include "test_helpers.h"
#include "test_instruction.h"

// Test loading a value into a registers
void testLDAImm() {
    Memory mem;
    CPU cpu(mem);

    // Load LDA_IMM instruction at address 0
    mem.write(0x0000, LDA_IMM);
    mem.write(0x0001, 0x42);
    cpu.reset();

    cpu.executeInstruction();

    EXPECT_TRUE(cpu.getRegister('A')  == 0x42);
}