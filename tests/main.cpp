#include "test_helpers.h"

#include "test_memory.h"
#include "test_flags.h"
#include "instructions/test_instruction.h"


int main() {

    testMemoryReadWrite();
    testFlags();
    testLDInstructions();
    testSTInstructions();
    
    std::cout << "All CPU/Memory tests passed.\n";

    return 0;
}