#include "../test_helpers.h"
#include "test_instruction.h"

void testSTInstructions() {
    Memory mem;
    CPU cpu(mem);

    PRINT_TEST_TITLE("TEST: ST Instructions");

    PRINT_TEST_SUBTITLE("Register A | STA_ZP");
    mem.write(0x0000,static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STA_ZP));
    mem.write(0x0003, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010) == 0x20);

    PRINT_TEST_SUBTITLE("Register X | STX_ZP");
    cpu.reset();
    mem.write(0x0000,static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STX_ZP));
    mem.write(0x0003, 0x15);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0015) == 0x20);

    PRINT_TEST_SUBTITLE("Register Y | STY_ZP");
    cpu.reset();
    mem.write(0x0000,static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STY_ZP));
    mem.write(0x0003, 0x30);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0030) == 0x20);

    mem.read_memory_block(0,50);
}