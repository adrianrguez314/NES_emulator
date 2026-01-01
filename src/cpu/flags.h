#ifndef flags_h
#define flags_h

#include <cstdint>

struct Flags {
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

    static inline void set(uint8_t &p, Flag f) {
        p |= (1 << f);
    }

    static inline void clear(uint8_t &p, Flag f) {
        p &= ~(1 << f);
    }

    static inline bool isSet(uint8_t p, Flag f) {
        return p & (1 << f);
    }

    static inline void updateZN(uint8_t &p, uint8_t v) {
        (v == 0) ? set(p, ZERO) : clear(p, ZERO);
        (v & 0x80) ? set(p, NEGATIVE) : clear(p, NEGATIVE);
    }

    static inline void updateCarry(uint8_t &p, uint16_t r) {
        (r > 0xFF) ? set(p, CARRY) : clear(p, CARRY);
    }

    static inline void updateOverflow(uint8_t &p, uint8_t a, uint8_t b, uint8_t r) {
        ((~(a ^ b) & (a ^ r)) & 0x80)
            ? set(p, OVERFLOW)
            : clear(p, OVERFLOW);
    }
};
#endif // flags_h