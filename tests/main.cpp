#include "test_helpers.h"

#include "test_memory.h"
#include "test_flags.h"
#include "test_instruction.h"


int main() {

    testMemoryReadWrite();
    testFlags();
    testLDAImm();
    
    std::cout << "All CPU/Memory tests passed.\n";

    return 0;
}