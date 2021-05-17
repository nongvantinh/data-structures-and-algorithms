#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch2/Catch.hpp"

// warning: Do not write your tests in header files!/
// It causes compile time increase greatly, because the way Catch2 single header file work.