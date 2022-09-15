#include "example.h"
#include <malloc.h>
#include <string.h>

bool fuzz_me(const uint8_t *data, size_t size)
{
    return size >= 3 &&
        data[0] == 'F' &&
        data[1] == 'U' &&
        data[2] == 'Z' &&
        data[3] == 'Z';  // :‑<
}
#if 0
int cppcheck_me(uint8_t *data, size_t size)
{
    size_t result = 1;
    if (size > 1 && size < result)
    {
        return 0;
    }
    if (size > 4 && size > 4)
    {
        return 3;
    }
    if (size >= 3 &&
        data[0] == 'F' &&
        data[1] == 'U' &&
        data[2] == 'Z' &&
        data[3] == 'Z')
    {
        result = 2;
        free(data);
    }
    free(data);
    return result;
}
#endif
#if 1
bool fuzz_me_too(const uint8_t *data, size_t size, uint8_t value)
{
    uint8_t *buffer = NULL;
    bool result = false;
    if (size >= 4 && value == '!')
    {
        buffer = (uint8_t*)malloc(4);
    }
    if (size >= 4 &&
        data[0] == 'F' &&
        data[1] == 'U' &&
        data[2] == 'Z' &&
        data[3] == 'Z')
    {
        buffer = (uint8_t*)malloc(4);
        result = true;
    }
    free(buffer);
    return result;
}
#endif
