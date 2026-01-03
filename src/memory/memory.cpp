#include <iostream>
#include <iomanip>

#include "memory.h"

Memory::Memory() {
    std::cout << "Memory initialized.\n";
}

Memory::~Memory() {
    std::cout << "Memory destroyed.\n";
}

uint8_t Memory::read(uint16_t addr) {
    return memoryData[addr % MEMORY_SIZE];
}

void Memory::write(uint16_t addr, uint8_t value) {
    memoryData[addr % MEMORY_SIZE] = value;
}

uint16_t Memory::read_u16(uint16_t addr) {
    uint8_t low = this->read(addr);
    uint8_t high = read(addr + 1);

    return static_cast<uint16_t>(high) << 8 | low;
}

void Memory::write_u16(uint16_t addr, uint16_t value) {
    uint8_t low = value & 0xFF;
    uint8_t high = value >> 8;

    this->write(addr,low);
    this->write(addr + 1, high);
}

void Memory::read_memory_block(int start, int length) {
    for(int line = 0; line < length; line += 16) {
        int addr = start + line;
        std::cout << std::setw(4) << std::setfill('0') << std::hex << addr << ": ";
        for(int i = 0; i < 16 && (addr + i) < start + length; i++) {
            std::cout << std::setw(2) << std::setfill('0') << std::hex
                      << +memoryData[(addr + i) % MEMORY_SIZE] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::dec;
}