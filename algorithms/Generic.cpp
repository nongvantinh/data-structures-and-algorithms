#include "Generic.h"

bool dsaa::is_prime(size_t p_number)
{
    if (p_number < 2)
        return false;
    size_t sr = std::sqrt(p_number);
    for (size_t i(2); i <= sr; ++i)
    {
        if (0 == p_number % i)
            return false;
    }
    return true;
}
