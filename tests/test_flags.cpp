#include <gtest/gtest.h>
#include "../src/cpu/flags.h"// Ajusta la ruta según tu proyecto

// Test básico de set/clear de Carry
TEST(Flags, SetClearCarry) {
    uint8_t status = 0;

    Flags::set(status, Flags::CARRY);
    EXPECT_TRUE(Flags::isSet(status, Flags::CARRY));

    Flags::clear(status, Flags::CARRY);
    EXPECT_FALSE(Flags::isSet(status, Flags::CARRY));
}

// Test de Zero y Negative flags
TEST(Flags, ZeroNegativeFlags) {
    uint8_t status = 0;
    Flags::updateZN(status, 0x00);
    EXPECT_TRUE(Flags::isSet(status, Flags::ZERO));
    EXPECT_FALSE(Flags::isSet(status, Flags::NEGATIVE));

    status = 0;
    Flags::updateZN(status, 0x80);
    EXPECT_FALSE(Flags::isSet(status, Flags::ZERO));
    EXPECT_TRUE(Flags::isSet(status, Flags::NEGATIVE));
}

// Test de Overflow flag
TEST(Flags, OverflowFlag) {
    uint8_t status = 0;
    Flags::updateOverflow(status, 0x50, 0x50, 0xA0);
    EXPECT_TRUE(Flags::isSet(status, Flags::OVERFLOW));

    status = 0;
    Flags::updateOverflow(status, 0x10, 0x10, 0x20);
    EXPECT_FALSE(Flags::isSet(status, Flags::OVERFLOW));
}