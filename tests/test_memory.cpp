#include "test_helpers.h"
#include "test_memory.h"

void testMemoryReadWrite() {
    Memory mem;
    mem.write(0x0001, 0x30);
    EXPECT_TRUE(mem.read(0x0001) == 0x30);
}