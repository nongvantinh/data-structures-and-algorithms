#include "Random.h"

bool dsaa::random::random_bool(double p_probability_of_true)
{
    std::random_device device;
    std::mt19937 engine(device());
    std::bernoulli_distribution distribution(p_probability_of_true);
    return distribution(engine);
}
