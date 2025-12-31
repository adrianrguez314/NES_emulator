#include <iostream>

#include "memory.h"

Memory::Memory() {
    std::cout << "Memory initialized.\n";

    memoryData = { 0 } ;
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