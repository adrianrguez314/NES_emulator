#include <gtest/gtest.h>
#include "../src/memory/memory.h"

TEST(Memory, ReadWriteByte) {
    Memory mem;
    mem.write(0x0001, 0x30);
    EXPECT_EQ(mem.read(0x0001), 0x30);
}

TEST(Memory, ReadWriteU16) {
    Memory mem;
    mem.write_u16(0x0002, 0x3535);
    EXPECT_EQ(mem.read_u16(0x0002), 0x3535);
}