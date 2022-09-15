#include "example.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) 
{
    fuzz_me(data, size);
    return 0;
}
