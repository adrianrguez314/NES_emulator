#include "../test_helpers.h"
#include "test_instruction.h"

void testSTInstructions() {
    Memory mem;
    CPU cpu(mem);

    PRINT_TEST_TITLE("TEST: ST Instructions");

    // Test STA instruction

    PRINT_TEST_SUBTITLE("Register A | STA_ZP");
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STA_ZP));
    mem.write(0x0003, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010) == 0x20);

    PRINT_TEST_SUBTITLE("Register A | STA_ZPX");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x05);
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0003, 0x30);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STA_ZPX));
    mem.write(0x0005, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0015) == 0x30);

    PRINT_TEST_SUBTITLE("Register A | STA_ABS");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x40);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STA_ABS));
    mem.write_u16(0x0003, 0x4020);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x4020) == 0x40);

    PRINT_TEST_SUBTITLE("Register A | STA_ABSX");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0003, 0x55);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STA_ABSX));
    mem.write_u16(0x0005, 0x2000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x2010) == 0x55);

    PRINT_TEST_SUBTITLE("Register A | STA_ABSY");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0x08);
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0003, 0x66);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STA_ABSY));
    mem.write_u16(0x0005, 0x3000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x3008) == 0x66);

    PRINT_TEST_SUBTITLE("Register A | STA_INX");
    cpu.reset();

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x77);
    cpu.executeInstruction();  

    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0003, 0x02);
    cpu.executeInstruction();  

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STA_INX));
    mem.write(0x0005, 0x04);      
    mem.write(0x06, 0x50);        
    mem.write(0x07, 0x60);      
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x6052) == 0x77);  

    PRINT_TEST_SUBTITLE("Register A | STA_INY");
    cpu.reset();

    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDA_IMM));
    mem.write(0x0001, 0x88);
    cpu.executeInstruction();  

    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0003, 0x03);
    cpu.executeInstruction();  

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STA_INY));
    mem.write(0x0005, 0x20);     
    mem.write(0x20, 0x40);      
    mem.write(0x21, 0x50);        
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x5043) == 0x88);

    // Test STX instruction

    PRINT_TEST_SUBTITLE("Register X | STX_ZP");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x77);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STX_ZP));
    mem.write(0x0003, 0x20);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0020) == 0x77);

    PRINT_TEST_SUBTITLE("Register X | STX_ZPY");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0x04);
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0003, 0x88);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STX_ZPY));
    mem.write(0x0005, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0014) == 0x88);

    PRINT_TEST_SUBTITLE("Register X | STX_ABS");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x99);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STX_ABS));
    mem.write_u16(0x0003, 0x5000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x5000) == 0x99);

    // Test STY instruction

    PRINT_TEST_SUBTITLE("Register Y | STY_ZP");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0xAA);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STY_ZP));
    mem.write(0x0003, 0x30);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0030) == 0xAA);

    PRINT_TEST_SUBTITLE("Register Y | STY_ZPX");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDX_IMM));
    mem.write(0x0001, 0x03);
    mem.write(0x0002, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0003, 0xBB);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Opcode::STY_ZPX));
    mem.write(0x0005, 0x20);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0023) == 0xBB);

    PRINT_TEST_SUBTITLE("Register Y | STY_ABS");
    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Opcode::LDY_IMM));
    mem.write(0x0001, 0xCC);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Opcode::STY_ABS));
    mem.write_u16(0x0003, 0x6000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x6000) == 0xCC);
}
