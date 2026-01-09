#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/memory/memory.h"
#include "../../src/cpu/opcodes.h"

TEST(ShiftInstructions, ASL_Accumulator_And_Memory) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x80); // 1000 0000
    mem.write(0x0002, static_cast<uint8_t>(Ops::ASL_ACC));
    
    cpu.executeInstruction(); 
    cpu.executeInstruction(); 
    
    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));

    mem.write(0x0003, static_cast<uint8_t>(Ops::ASL_ZP));
    mem.write(0x0004, 0x10);
    mem.write(0x0010, 0x01);
    
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010), 0x02);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
}

TEST(ShiftInstructions, LSR_Accumulator_And_Memory) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x01);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LSR_ACC));
    
    cpu.executeInstruction();
    cpu.executeInstruction();
    
    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));

    mem.write(0x0003, static_cast<uint8_t>(Ops::LSR_ZP));
    mem.write(0x0004, 0x20);
    mem.write(0x0020, 0x80);
    
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0020), 0x40);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));
}

TEST(ShiftInstructions, ROL_Accumulator_With_Carry) {
    Memory mem;
    CPU cpu(mem);

    cpu.getFlags().set(Flags::CARRY);
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x80);
    mem.write(0x0002, static_cast<uint8_t>(Ops::ROL_ACC));

    cpu.executeInstruction(); 
    cpu.executeInstruction(); 

    EXPECT_EQ(cpu.getRegister('A'), 0x01);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY)); 
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
}

TEST(ShiftInstructions, ROR_Memory_With_Carry) {
    Memory mem;
    CPU cpu(mem);

    cpu.getFlags().set(Flags::CARRY);
    mem.write(0x0000, static_cast<uint8_t>(Ops::ROR_ZP));
    mem.write(0x0001, 0x30);
    mem.write(0x0030, 0x01);

    cpu.executeInstruction();

    EXPECT_EQ(mem.read(0x0030), 0x80);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));   
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::NEGATIVE)); 
}