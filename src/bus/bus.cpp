#include <iostream>
#include <iomanip>

#include "bus.h"

Bus::Bus() {
    std::cout << "Bus initialized.\n";
}

Bus::~Bus() {
    std::cout << "Bus destroyed.\n";
}

uint8_t Bus::read(uint16_t addr) {
    return memoryData[addr % MEMORY_SIZE];
}

void Bus::write(uint16_t addr, uint8_t value) {
    memoryData[addr % MEMORY_SIZE] = value;
}

uint16_t Bus::read_u16(uint16_t addr) {
    uint8_t low = this->read(addr);
    uint8_t high = read(addr + 1);

    return static_cast<uint16_t>(high) << 8 | low;
}

void Bus::write_u16(uint16_t addr, uint16_t value) {
    uint8_t low = value & 0xFF;
    uint8_t high = value >> 8;

    this->write(addr,low);
    this->write(addr + 1, high);
}