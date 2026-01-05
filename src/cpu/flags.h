#ifndef flags_h
#define flags_h

#include <cstdint>

#undef OVERFLOW


#include <cstdint>

class Flags {
public:
    enum Flag : uint8_t {
        CARRY = 0,
        ZERO = 1,
        INTERRUPT_DISABLE = 2,
        DECIMAL_MODE = 3,
        BREAK_COMMAND = 4,
        UNUSED = 5,
        OVERFLOW = 6,
        NEGATIVE = 7
    };

    Flags() : p(0x24) {} 

    void set(Flag f)    { p |=  (1 << f); }
    void clear(Flag f)  { p &= ~(1 << f); }
    bool isSet(Flag f) const { return (p & (1 << f)) != 0; }

    uint8_t raw() const { return p; }
    void raw(uint8_t v) { p = v; }

    void updateZN(uint8_t v) {
        (v == 0) ? set(ZERO) : clear(ZERO);
        (v & 0x80) ? set(NEGATIVE) : clear(NEGATIVE);
    }

    void updateCarry(uint16_t r) {
        (r > 0xFF) ? set(CARRY) : clear(CARRY);
    }

    void updateOverflow(uint8_t a, uint8_t b, uint8_t r) {
        ((~(a ^ b) & (a ^ r)) & 0x80)
            ? set(OVERFLOW)
            : clear(OVERFLOW);
    }

private:
    uint8_t p;
};

#endif // flags_h