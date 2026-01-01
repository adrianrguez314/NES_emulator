#include "test_helpers.h"

#include "test_memory.h"
#include "test_flags.h"
#include "test_instruction.h"


int main() {

    std::cout << "------------------------\n";
    std::cout << "Memory Test Suite\n";
    std::cout << "------------------------\n\n";
    testMemoryReadWrite();

    std::cout << "\n------------------------\n";
    std::cout << "Flags Test Suite\n";
    std::cout << "------------------------\n\n";
    testFlags();

    std::cout << "\n------------------------\n";
    std::cout << "Instructions Test Suite\n";
    std::cout << "------------------------\n\n";
    testLDAImm();

    std::cout << "All CPU/Memory tests passed.\n";
    return 0;
}