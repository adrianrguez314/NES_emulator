#ifndef test_helpers_h
#define test_helpers_h

#include <cassert>
#include <iostream>

#include "../src/cpu/cpu.h"
#include "../src/memory/memory.h"
#include "../src/cpu/opcodes.h"
#include "../src/cpu/flags.h"

#define EXPECT_EQ(expr) \
    if (!(expr)) std::cerr << "[FAIL] " #expr << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
    else std::cout << "[PASS] " #expr << "\n";

#define EXPECT_REG_EQ(cpu, reg, expected)                                 \
    do {                                                                  \
        char __r = (reg);                                                 \
        uint8_t __v = (cpu).getRegister(__r);                             \
        if (__v != (expected)) {                                          \
            std::cerr << "[FAIL] cpu.getRegister('" << __r << "') == 0x"  \
                      << std::hex << (int)(expected)                      \
                      << " (got 0x" << (int)__v << ")"                    \
                      << std::dec << " at " << __FILE__                   \
                      << ":" << __LINE__ << "\n";                         \
        } else {                                                          \
            std::cout << "[PASS] cpu.getRegister('" << __r << "') == 0x"  \
                      << std::hex << (int)(expected)                      \
                      << std::dec << "\n";                                \
        }                                                                 \
    } while (0)

#define PRINT_TEST_TITLE(name)                               \
    do {                                                    \
        std::cout << "\n+--------------------------------+\n"; \
        std::cout << "| TEST: " << name << "\n";           \
        std::cout << "+--------------------------------+\n"; \
    } while (0)

#define PRINT_TEST_SUBTITLE(name) std::cout << "\n|-> " << name << " <-|\n";



#endif // test helpers_h