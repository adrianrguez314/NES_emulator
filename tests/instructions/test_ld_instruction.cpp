#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/memory/memory.h"
#include "../../src/cpu/opcodes.h"
#include "../../src/cpu/flags.h"

TEST(LDInstructions, Immediate) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x42);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x42); 

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x10);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x55);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x55);
}

TEST(LDInstructions, ZeroPage) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0010, 0x65);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_ZP));
    mem.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x65);

    mem.write(0x0010, 0x77);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_ZP));
    mem.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x77);

    mem.write(0x0010, 0x88);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_ZP));
    mem.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x88);
}

TEST(LDInstructions, ZeroPageIndexed) {
    Memory mem;
    CPU cpu(mem);

    
    mem.write(0x0090, 0x42);  
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_ZPX));
    mem.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('A'), 0x42);

    cpu.reset();
    mem.write(0x0090, 0x42);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDX_ZPY));
    mem.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x42);

    cpu.reset();
    mem.write(0x0090, 0x42);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDY_ZPX));
    mem.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x42);
}


TEST(LDInstructions, Absolute) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x1255, 0x88);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_ABS));
    mem.write_u16(0x0001, 0x1255);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x88);

    mem.write(0x1300, 0x77);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_ABS));
    mem.write_u16(0x0001, 0x1300);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x77);

    mem.write(0x1400, 0x66);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_ABS));
    mem.write_u16(0x0001, 0x1400);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x66);
}

TEST(LDInstructions, AbsoluteIndexed) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x2030, 0x55); 
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_ABSX));
    mem.write_u16(0x0003, 0x2020);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('A'), 0x55);

    cpu.reset();
    mem.write(0x2030, 0x66); 
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDX_ABSY));
    mem.write_u16(0x0003, 0x2020);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x66);

    cpu.reset();
    mem.write(0x2030, 0x77); 
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDY_ABSX));
    mem.write_u16(0x0003, 0x2020);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x77);
}

TEST(LDInstructions, IndirectX) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x04);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_INX));
    mem.write(0x0003, 0x02);

    mem.write(0x06, 0x10);
    mem.write(0x07, 0x20);
    mem.write(0x2010, 0x42);

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x42);
}

TEST(LDInstructions, IndirectY) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x05);
    cpu.reset();
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_INY));
    mem.write(0x0003, 0x10);

    mem.write(0x10, 0x20);
    mem.write(0x11, 0x30);
    mem.write(0x3025, 0x99);

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x99);
}

