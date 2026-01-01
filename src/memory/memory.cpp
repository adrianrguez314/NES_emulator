#include <iostream>

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