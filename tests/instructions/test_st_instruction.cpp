#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/memory/memory.h"
#include "../../src/cpu/opcodes.h"


TEST(STInstructions, STA) {
    Memory mem;
    CPU cpu(mem);

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x20);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STA_ZP));
    mem.write(0x0003, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0010), 0x20);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x05);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0003, 0x30);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Ops::STA_ZPX));
    mem.write(0x0005, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0015), 0x30);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x40);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STA_ABS));
    mem.write_u16(0x0003, 0x4020);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x4020), 0x40);

    /*cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x10);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0003, 0x55);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Ops::STA_ABSX));
    mem.write_u16(0x0005, 0x2000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x2010), 0x55);*/

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x08);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0003, 0x66);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Ops::STA_ABSY));
    mem.write_u16(0x0005, 0x3000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x3008), 0x66);

    cpu.reset();

    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x77);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0003, 0x02);
    cpu.executeInstruction();

    mem.write(0x0006, 0x52); 
    mem.write(0x0007, 0x60); 
    mem.write(0x0004, static_cast<uint8_t>(Ops::STA_INX));
    mem.write(0x0005, 0x04);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x6052), 0x77);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    mem.write(0x0001, 0x88);
    cpu.executeInstruction();  

    mem.write(0x0002, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0003, 0x03);
    cpu.executeInstruction();  

    mem.write(0x0004, static_cast<uint8_t>(Ops::STA_INY));
    mem.write(0x0005, 0x20);     
    mem.write(0x20, 0x40);      
    mem.write(0x21, 0x50);        
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x5043), 0x88);
}

TEST(STInstructions, STX) {
    Memory mem;
    CPU cpu(mem);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x77);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STX_ZP));
    mem.write(0x0003, 0x20);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0020), 0x77);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0x04);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0003, 0x88);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Ops::STX_ZPY));
    mem.write(0x0005, 0x10);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0014), 0x88);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x99);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STX_ABS));
    mem.write_u16(0x0003, 0x5000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x5000), 0x99);
}

TEST(STInstructions, STY) {
    Memory mem;
    CPU cpu(mem);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0xAA);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STY_ZP));
    mem.write(0x0003, 0x30);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0030), 0xAA);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    mem.write(0x0001, 0x03);
    mem.write(0x0002, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0003, 0xBB);
    cpu.executeInstruction();
    cpu.executeInstruction();

    mem.write(0x0004, static_cast<uint8_t>(Ops::STY_ZPX));
    mem.write(0x0005, 0x20);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x0023), 0xBB);

    cpu.reset();
    mem.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    mem.write(0x0001, 0xCC);
    cpu.executeInstruction();

    mem.write(0x0002, static_cast<uint8_t>(Ops::STY_ABS));
    mem.write_u16(0x0003, 0x6000);
    cpu.executeInstruction();
    EXPECT_EQ(mem.read(0x6000), 0xCC);
}
