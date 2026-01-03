#include "test_helpers.h"
#include "test_instruction.h"

// Test loading a value into registers
void testLDAImm() {

    PRINT_TEST_TITLE("TEST: Instructions");

    Memory mem;
    CPU cpu(mem);

    char registers[3] = {'A','X','Y'};
    Opcodes program[] = {
        LDA_IMM, LDA_ZP, LDA_ABS,  // A
        LDX_IMM, LDX_ZP, LDX_ABS,  // X
        LDY_IMM, LDY_ZP, LDY_ABS   // Y
    };

    for (int i = 0; i < 3; i++) {
        char reg = registers[i];

        mem.write(0x0000, program[i * 3 + 0]);
        mem.write(0x0001, 0x42);
        cpu.reset();

        PRINT_TEST_SUBTITLE("Mode addressing: IMMEDIATE");
        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x42);

        PRINT_TEST_SUBTITLE("Mode addressing: ZERO PAGE");
        mem.write(0x0010, 0x65);
        mem.write(0x0002, program[i * 3 + 1]);
        mem.write(0x0003, 0x10);

        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x65);

        PRINT_TEST_SUBTITLE("Mode addressing: ABSOLUTE");
        mem.write(0x1255, 0x88);
        mem.write(0x0004, program[i * 3 + 2]);
        mem.write_u16(0x0005, 0x1255);

        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x88);
    }
}
