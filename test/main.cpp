#define CATCH_CONFIG_RUNNER
#include "Catch2/Catch.hpp"

int main(int argc, char *argv[])
{
    int result(0);
    // global setup...
    {
        result = Catch::Session().run(argc, argv);
    }

    // global clean-up...

    return result;
}

// warning: Do not write your tests in header files!/
// It causes compile time increase greatly, because Catch2 put everything in single header file.