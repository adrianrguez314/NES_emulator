#include "test_helpers.h"
#include "test_instruction.h"

// Test loading a value into a registers
void testLDAImm() {

    PRINT_TEST_TITLE("TEST: Instructions");

    Memory mem;
    CPU cpu(mem);


    // Load LDA instruction in addressing mode IMMEDIATE
    mem.write(0x0000, LDA_IMM);
    mem.write(0x0001, 0x42);
    cpu.reset();

    cpu.executeInstruction();
    EXPECT_TRUE(cpu.getRegister('A')  == 0x42);

    //Load LDA instruction in addressing mode ZERO PAGE
    mem.write(0x0010, 0x65);
    mem.write(0x0002, LDA_ZP);
    mem.write(0x0003, 0x10);

    cpu.executeInstruction();
    EXPECT_TRUE(cpu.getRegister('A')  == 0x65);

    //Load LDA instruction in addressing mode ABSOLUTE
    mem.write (0x1255,0x88);
    mem.write(0x0004,LDA_ABS);
    mem.write_u16(0x0005,0x1255);

    cpu.executeInstruction();
    EXPECT_TRUE(cpu.getRegister('A') == 0x88)
}