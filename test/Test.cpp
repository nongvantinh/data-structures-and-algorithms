#include "test/Test.h"

unsigned int dsaa::random_range(unsigned int start, unsigned int end)
{
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end); // distribution in range [1, 6]
    return dist6(engine);
}
