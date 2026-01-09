#include <gtest/gtest.h>
#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"

struct JumpTestCase {
    uint8_t opcode;        
    CPU::AddressingMode mode;
    uint16_t baseAddr;    
    uint16_t expectedPC;  
    const char* name;
};

class JumpInstructions : public ::testing::TestWithParam<JumpTestCase> {
protected:
    Memory mem;
    CPU cpu{mem};
};

TEST_P(JumpInstructions, Execute) {
    auto test = GetParam();
    cpu.reset();

    if (test.mode == CPU::AddressingMode::Absolute) {

        mem.write(0xFFFC, static_cast<uint8_t>(test.opcode));
        mem.write(0xFFFD, static_cast<uint8_t>(test.baseAddr & 0xFF));
        mem.write(0xFFFE, static_cast<uint8_t>((test.baseAddr >> 8) & 0xFF));
    } else if (test.mode == CPU::AddressingMode::Indirect) {

        mem.write(0xFFFC, static_cast<uint8_t>(test.opcode));
        mem.write(0xFFFD, static_cast<uint8_t>(test.baseAddr & 0xFF));   
        mem.write(0xFFFE, static_cast<uint8_t>((test.baseAddr >> 8) & 0xFF)); 

        uint16_t ptr = test.baseAddr; 
        uint16_t target = test.expectedPC;

        uint16_t highAddr = ((ptr & 0x00FF) == 0xFF) ? (ptr & 0xFF00) : ptr + 1;

        mem.write(ptr, static_cast<uint8_t>(target & 0xFF));           
        mem.write(highAddr, static_cast<uint8_t>((target >> 8) & 0xFF)); 
        }

    cpu.setPC(0xFFFC);
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), test.expectedPC);
}

INSTANTIATE_TEST_SUITE_P(
    JumpTests,
    JumpInstructions,
    ::testing::Values(
        JumpTestCase{Ops::JMP_ABS, CPU::AddressingMode::Absolute, 0x1234, 0x1234, "JMP_ABS_basic"},
        JumpTestCase{Ops::JMP_IND, CPU::AddressingMode::Indirect, 0x2000, 0x3456, "JMP_IND_basic"},
        JumpTestCase{Ops::JMP_IND, CPU::AddressingMode::Indirect, 0x30FF, 0x78AB, "JMP_IND_bug"},
        JumpTestCase{Ops::JSR, CPU::AddressingMode::Absolute, 0x4000, 0x4000, "JSR_ABS_basic"}
    ),
    [](const ::testing::TestParamInfo<JumpTestCase>& info) {
        return std::string(info.param.name);
    }
);
