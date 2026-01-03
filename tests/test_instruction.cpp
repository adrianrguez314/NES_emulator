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

        PRINT_TEST_SUBTITLE("Adressing mode: IMMEDIATE");
        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x42);

        PRINT_TEST_SUBTITLE("Addressing mode: ZERO_PAGE");
        mem.write(0x0010, 0x65);
        mem.write(0x0002, program[i * 3 + 1]);
        mem.write(0x0003, 0x10);

        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x65);

        PRINT_TEST_SUBTITLE("Addresing mode: ABSOLUTE");
        mem.write(0x1255, 0x88);
        mem.write(0x0004, program[i * 3 + 2]);
        mem.write_u16(0x0005, 0x1255);

        cpu.executeInstruction();
        EXPECT_REG_EQ(cpu, reg, 0x88);
    }

PRINT_TEST_TITLE("TEST: ZERO_PAGE indexed addressing modes");

cpu.reset();
PRINT_TEST_SUBTITLE("Register A | LDA_ZPX");

mem.write(0x0090, 0x42);   // (0x80 + 0x10) = 0x90

mem.write(0x0000, LDX_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDA_ZPX);
mem.write(0x0003, 0x80);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'A', 0x42);

cpu.reset();
PRINT_TEST_SUBTITLE("Register X | LDX_ZPY");

mem.write(0x0090, 0x42);   // (0x80 + 0x10) = 0x90

mem.write(0x0000, LDY_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDX_ZPY);
mem.write(0x0003, 0x80);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'Y', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x42);

cpu.reset();
PRINT_TEST_SUBTITLE("Register Y | LDY_ZPX");

mem.write(0x0090, 0x42);   // (0x80 + 0x10) = 0x90

mem.write(0x0000, LDX_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDY_ZPX);
mem.write(0x0003, 0x80);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'Y', 0x42);

PRINT_TEST_TITLE("TEST: ABSOLUTE indexed addressing modes");

PRINT_TEST_SUBTITLE("Register A | LDA_ABSX");

mem.write(0x2030, 0x55);   // 0x2020 + 0x10 = 0x2030

mem.write(0x0000, LDX_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDA_ABSX);
mem.write_u16(0x0003, 0x2020);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'A', 0x55);


cpu.reset();
PRINT_TEST_SUBTITLE("Register X | LDX_ABSY");

mem.write(0x2030, 0x66);   // 0x2020 + 0x10 = 0x2030

mem.write(0x0000, LDY_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDX_ABSY);
mem.write_u16(0x0003, 0x2020);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'Y', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x66);


cpu.reset();
PRINT_TEST_SUBTITLE("Register Y | LDY_ABSX");

mem.write(0x2030, 0x77);   // 0x2020 + 0x10 = 0x2030

mem.write(0x0000, LDX_IMM);
mem.write(0x0001, 0x10);

mem.write(0x0002, LDY_ABSX);
mem.write_u16(0x0003, 0x2020);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'X', 0x10);

cpu.executeInstruction();
EXPECT_REG_EQ(cpu, 'Y', 0x77);
}

