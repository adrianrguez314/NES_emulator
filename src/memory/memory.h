#ifndef memory_h
#define memory_h

#include <cstdint>
#include <array>

#define MEMORY_SIZE 2* 1024 // 2KB of RAM

class Memory {
    public:
        Memory();
        ~Memory();

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t value);

    private:
        std::array<uint8_t, MEMORY_SIZE> memoryData;
};

#endif // memory_h