#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"
#include "../../src/cpu/flags.h"

struct CompareTestCase {
    Opcode opcode;
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
        case Opcode::CMP_IMM:
            cpu.setA(test.reg_init);
            break;

        case Opcode::CPX_IMM:
            cpu.setX(test.reg_init);
            break;

        case Opcode::CPY_IMM:
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
        CompareTestCase{Opcode::CMP_IMM, CPU::AddressingMode::Immediate, 0x50, 0x50, true, true, false, "CMP_IMM_eq"},
        CompareTestCase{Opcode::CMP_IMM, CPU::AddressingMode::Immediate, 0x60, 0x50, true, false, false, "CMP_IMM_gt"},
        CompareTestCase{Opcode::CMP_IMM, CPU::AddressingMode::Immediate, 0x40, 0x50, false, false, true, "CMP_IMM_lt"},

        CompareTestCase{Opcode::CPX_IMM, CPU::AddressingMode::Immediate, 0x10, 0x10, true, true, false, "CPX_IMM_eq"},
        CompareTestCase{Opcode::CPX_IMM, CPU::AddressingMode::Immediate, 0x20, 0x10, true, false, false, "CPX_IMM_gt"},
        CompareTestCase{Opcode::CPX_IMM, CPU::AddressingMode::Immediate, 0x05, 0x10, false, false, true, "CPX_IMM_lt"},

        CompareTestCase{Opcode::CPY_IMM, CPU::AddressingMode::Immediate, 0x30, 0x30, true, true, false, "CPY_IMM_eq"},
        CompareTestCase{Opcode::CPY_IMM, CPU::AddressingMode::Immediate, 0x40, 0x30, true, false, false, "CPY_IMM_gt"},
        CompareTestCase{Opcode::CPY_IMM, CPU::AddressingMode::Immediate, 0x20, 0x30, false, false, true, "CPY_IMM_lt"}
    ),
    [](const ::testing::TestParamInfo<CompareTestCase>& info) {
        return std::string(info.param.name);
    }
);