#include "test_helpers.h"
#include "test_memory.h"

void testMemoryReadWrite() {

    PRINT_TEST_TITLE("TEST: Memory (RAM)");

    Memory mem;

    mem.write(0x0001, 0x30);
    EXPECT_EQ(mem.read(0x0001) == 0x30);

    mem.write_u16(0x0002, 0x3535);
    EXPECT_EQ(mem.read_u16(0x0002) == 0x3535);
}