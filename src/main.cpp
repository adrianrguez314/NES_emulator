#include <iostream>

#include "./cpu/cpu.h"
#include "./memory/memory.h"


int main () {
    Memory memory;

    CPU cpu(memory);
    cpu.reset();
    cpu.executeInstruction();
    return 0;
}