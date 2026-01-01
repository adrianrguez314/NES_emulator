#include <cassert>
#include <iostream>

#include "../src/cpu/cpu.h"
#include "../src/memory/memory.h"
#include "../src/cpu/opcodes.h"
#include "../src/cpu/flags.h"

#define EXPECT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            std::cerr << "[FAIL] " #expr << "\n"; \
            std::abort(); \
        } \
    } while (0)

// Test Memory read and write basic functionality

void testMemoryReadWrite() {
    Memory mem;
    mem.write(0x0001, 0x30);
    EXPECT_TRUE(mem.read(0x0001) == 0x30);
    std:: cout << "-> Test Memory Read/Write passed.\n";
}

// Test flags settings and clearing

void testFlags() {
    uint8_t status = 0;

    Flags::set(status, Flags::CARRY);
    EXPECT_TRUE(Flags::isSet(status, Flags::CARRY));

    Flags::clear(status, Flags::CARRY);
    EXPECT_TRUE(!Flags::isSet(status, Flags::CARRY));

    std::cout << "-> Set and Clear Carry flag test passed.\n";

    // Zero and Negative flag tests
    status = 0;
    Flags::updateZN(status, 0x00);
    EXPECT_TRUE(Flags::isSet(status, Flags::ZERO));
    EXPECT_TRUE(!Flags::isSet(status, Flags::NEGATIVE));

    status = 0;
    Flags::updateZN(status, 0x80);
    EXPECT_TRUE(Flags::isSet(status, Flags::ZERO));
    EXPECT_TRUE(!Flags::isSet(status, Flags::NEGATIVE));

    std::cout << "-> Zero and Negative flag tests passed.\n";

    // Overflow flag test
    status = 0;
    Flags::updateOverflow(status, 0x50, 0x50, 0xA0);
    EXPECT_TRUE(Flags::isSet(status, Flags::OVERFLOW));

    std::cout << "-> Overflow flag tests passed.\n";

}

// Test loading a value into a registers
void testLDAImm() {
    Memory mem;
    CPU cpu(mem);

    // Load LDA_IMM instruction at address 0
    mem.write(0x0000, LDA_IMM);
    mem.write(0x0001, 0x42);
    cpu.reset();

    cpu.executeInstruction();

    assert(cpu.getRegister('A')  == 0x42);
    std:: cout << "-> Test LDA_IMM passed. \n";
}

int main() {

    std::cout << "------------------------\n";
    std::cout << "Memory Test Suite\n";
    std::cout << "------------------------\n\n";
    testMemoryReadWrite();

    std::cout << "\n------------------------\n";
    std::cout << "Flags Test Suite\n";
    std::cout << "------------------------\n\n";
    testFlags();

    std::cout << "\n------------------------\n";
    std::cout << "Instructions Test Suite\n";
    std::cout << "------------------------\n\n";
    testLDAImm();

    std::cout << "All CPU/Memory tests passed.\n";
    return 0;
}