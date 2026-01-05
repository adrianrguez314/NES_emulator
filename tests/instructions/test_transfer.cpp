#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"


TEST(TransferInstructions, Transfers) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x40);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::TAX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x40);

    mem.write(0x0003, static_cast<uint8_t>(Opcode::TAY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x40);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x80);
    cpu.executeInstruction();
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0003, 0x12);
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::TXA));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x80);

    mem.write(0x0005, static_cast<uint8_t>(Opcode::TYA));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x12);
}