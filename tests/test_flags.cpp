#include "test_helpers.h"
#include "test_flags.h"

void testFlags() {

    PRINT_TEST_TITLE("TEST: Flags");

    uint8_t status = 0;

    Flags::set(status, Flags::CARRY);
    EXPECT_EQ(Flags::isSet(status, Flags::CARRY));

    Flags::clear(status, Flags::CARRY);
    EXPECT_EQ(!Flags::isSet(status, Flags::CARRY));

    // Zero and Negative flag tests
    status = 0;
    Flags::updateZN(status, 0x00);
    EXPECT_EQ(Flags::isSet(status, Flags::ZERO));
    EXPECT_EQ(!Flags::isSet(status, Flags::NEGATIVE));

    status = 0;
    Flags::updateZN(status, 0x80);
    EXPECT_EQ(!Flags::isSet(status, Flags::ZERO));
    EXPECT_EQ(Flags::isSet(status, Flags::NEGATIVE));

    // Overflow flag test
    status = 0;
    Flags::updateOverflow(status, 0x50, 0x50, 0xA0);
    EXPECT_EQ(Flags::isSet(status, Flags::OVERFLOW));

    status = 0;
    Flags::updateOverflow(status, 0x10, 0x10, 0x20);
    EXPECT_EQ(!Flags::isSet(status, Flags::OVERFLOW));

}
