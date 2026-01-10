#ifndef bus_h
#define bus_h

#include <cstdint>
#include <array>

class Bus {
    public:
        Bus();
        ~Bus();

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t value);

        uint16_t read_u16 (uint16_t addr);
        void write_u16 (uint16_t addr, uint16_t value);

    private:
        static constexpr int MEMORY_SIZE = 64 * 1024; // RAM 64Kb
        std::array<uint8_t, MEMORY_SIZE> memoryData { };
};

#endif // bus_h