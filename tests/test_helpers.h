#ifndef test_helpers_h
#define test_helpers_h

#include <cassert>
#include <iostream>

#include "../src/cpu/cpu.h"
#include "../src/memory/memory.h"
#include "../src/cpu/opcodes.h"
#include "../src/cpu/flags.h"

#define EXPECT_TRUE(expr) \
    if (!(expr)) std::cerr << "[FAIL] " #expr << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
    else std::cout << "[PASS] " #expr << "\n";

#define PRINT_TEST_TITLE(name)                                     \
    do {                                                    \
        std::cout << "\n+--------------------------------+\n"; \
        std::cout << "| TEST: " << name << "\n";           \
        std::cout << "+--------------------------------+\n"; \
    } while (0)

#endif // test helpers_h