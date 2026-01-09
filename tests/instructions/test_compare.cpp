#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"
#include "../../src/cpu/flags.h"

struct CompareTestCase {
    uint8_t opcode;
    CPU::AddressingMode mode;
    uint8_t reg_init;  
    uint8_t mem_value; 
    bool expectedC;
    bool expectedZ;
    bool expectedN;
    const char* name;
};

class CompareInstructions : public ::testing::TestWithParam<CompareTestCase> {
protected:
    Memory mem;
    CPU cpu{mem};
};

TEST_P(CompareInstructions, Execute) {
    auto test = GetParam();

    cpu.reset();

    switch (test.opcode) {
        case Ops::CMP_IMM:
            cpu.setA(test.reg_init);
            break;

        case Ops::CPX_IMM:
            cpu.setX(test.reg_init);
            break;

        case Ops::CPY_IMM:
            cpu.setY(test.reg_init);
            break;

        default:
            FAIL() << "Opcode don't suport in this test";
    }

    mem.write(0x0000, static_cast<uint8_t>(test.opcode));
    mem.write(0x0001, test.mem_value);                   

    cpu.executeInstruction();

    EXPECT_EQ(cpu.getFlags().isSet(Flags::CARRY), test.expectedC);
    EXPECT_EQ(cpu.getFlags().isSet(Flags::ZERO), test.expectedZ);
    EXPECT_EQ(cpu.getFlags().isSet(Flags::NEGATIVE), test.expectedN);
}


INSTANTIATE_TEST_SUITE_P(
    CompareTests,
    CompareInstructions,
    ::testing::Values(
        CompareTestCase{Ops::CMP_IMM, CPU::AddressingMode::Immediate, 0x50, 0x50, true, true, false, "CMP_IMM_eq"},
        CompareTestCase{Ops::CMP_IMM, CPU::AddressingMode::Immediate, 0x60, 0x50, true, false, false, "CMP_IMM_gt"},
        CompareTestCase{Ops::CMP_IMM, CPU::AddressingMode::Immediate, 0x40, 0x50, false, false, true, "CMP_IMM_lt"},

        CompareTestCase{Ops::CPX_IMM, CPU::AddressingMode::Immediate, 0x10, 0x10, true, true, false, "CPX_IMM_eq"},
        CompareTestCase{Ops::CPX_IMM, CPU::AddressingMode::Immediate, 0x20, 0x10, true, false, false, "CPX_IMM_gt"},
        CompareTestCase{Ops::CPX_IMM, CPU::AddressingMode::Immediate, 0x05, 0x10, false, false, true, "CPX_IMM_lt"},

        CompareTestCase{Ops::CPY_IMM, CPU::AddressingMode::Immediate, 0x30, 0x30, true, true, false, "CPY_IMM_eq"},
        CompareTestCase{Ops::CPY_IMM, CPU::AddressingMode::Immediate, 0x40, 0x30, true, false, false, "CPY_IMM_gt"},
        CompareTestCase{Ops::CPY_IMM, CPU::AddressingMode::Immediate, 0x20, 0x30, false, false, true, "CPY_IMM_lt"}
    ),
    [](const ::testing::TestParamInfo<CompareTestCase>& info) {
        return std::string(info.param.name);
    }
);