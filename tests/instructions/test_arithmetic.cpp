#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"
#include "../../src/cpu/flags.h"


TEST(ArithmeticInstructions, INC_DEC_Memory) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::INC_ZP));
    mem.write(0x0001, 0x10);
    mem.write(0x0010, 0x05);

    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010), 0x06);

    mem.write(0x0002, static_cast<uint8_t>(Opcode::DEC_ZP));
    mem.write(0x0003, 0x10);

    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010), 0x05);
}

TEST(ArithmeticInstructions, INX_DEX) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x10);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::INX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x11);

    mem.write(0x0003, static_cast<uint8_t>(Opcode::DEX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
}

TEST(ArithmeticInstructions, INY_DEY) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::INY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x21);

    mem.write(0x0003, static_cast<uint8_t>(Opcode::DEY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x20);
}

TEST(ArithmeticInstructions, ADC_Immediate) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x10);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::ADC_IMM));
    mem.write(0x0003, 0x05);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x15);
}

TEST(ArithmeticInstructions, ADC_WrapAround) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0xFF);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::ADC_IMM));
    mem.write(0x0003, 0x02);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x01);
}

/*TEST(ArithmeticInstructions, SBC_Immediate) {
    Memory mem;
    CPU cpu(mem);

    cpu.setFlag(Flags::CARRY, true);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x10);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::SBC_IMM));
    mem.write(0x0003, 0x03);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x0D);
}

TEST(ArithmeticInstructions, SBC_WrapAround) {
    Memory mem;
    CPU cpu(mem);

    cpu.setFlag(Flags::CARRY, true);

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x00);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::SBC_IMM));
    mem.write(0x0003, 0x01);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0xFF);
}*/


