#include <gtest/gtest.h>
#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"

TEST(BranchInstructions, BEQ_Taken_Forward) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::ZERO);
    uint16_t initialPC = 0x8000;
    cpu.setPC(initialPC);

    bus.write(0x8000, static_cast<uint8_t>(Ops::BEQ));
    bus.write(0x8001, 0x05); 

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), 0x8007);
}

TEST(BranchInstructions, BNE_Not_Taken) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::ZERO); 
    uint16_t initialPC = 0x8000;
    cpu.setPC(initialPC);

    bus.write(0x8000, static_cast<uint8_t>(Ops::BNE));
    bus.write(0x8001, 0x05);

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), 0x8002);
}

TEST(BranchInstructions, BMI_Taken_Backward) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::NEGATIVE); 
    uint16_t initialPC = 0x8010;
    cpu.setPC(initialPC);

    bus.write(0x8010, static_cast<uint8_t>(Ops::BMI));
    bus.write(0x8011, 0xFB); 

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), 0x800D);
}

TEST(BranchInstructions, All_Flags_Check) {
    Bus bus;
    CPU cpu(bus);
    uint16_t pc = 0x8000;

    auto testBranch = [&](uint8_t op, Flags::Flag flag, bool setFlag, bool shouldJump) {
        cpu.setPC(pc);
        if (setFlag) cpu.getFlags().set(flag); else cpu.getFlags().clear(flag);
        bus.write(pc, op);
        bus.write(pc + 1, 0x10);
        
        cpu.executeInstruction();
        
        uint16_t expected = shouldJump ? pc + 2 + 16 : pc + 2;
        EXPECT_EQ(cpu.getPC(), expected);
        pc = cpu.getPC(); 
    };

    testBranch(static_cast<uint8_t>(Ops::BCC), Flags::CARRY, false, true);
    testBranch(static_cast<uint8_t>(Ops::BCS), Flags::CARRY, true, true);
    
    testBranch(static_cast<uint8_t>(Ops::BVC), Flags::OVERFLOW, false, true);
    testBranch(static_cast<uint8_t>(Ops::BVS), Flags::OVERFLOW, true, true);

    testBranch(static_cast<uint8_t>(Ops::BPL), Flags::NEGATIVE, false, true);
    testBranch(static_cast<uint8_t>(Ops::BMI), Flags::NEGATIVE, true, true);
}