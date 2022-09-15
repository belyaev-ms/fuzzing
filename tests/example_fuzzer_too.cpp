#include "example.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) 
{
    FuzzedDataProvider provider(data, size);
    uint8_t value = provider.ConsumeIntegral<uint8_t>();
    std::vector<uint8_t> buffer = provider.ConsumeRemainingBytes<uint8_t>();
    fuzz_me_too(&buffer[0], buffer.size(), value);
    return 0;
}
