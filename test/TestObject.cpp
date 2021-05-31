#include "TestObject.h"

struct verify
{
    ~verify()
    {
        std::cout << "livecount: " << dsaa::TestObject::livecount << std::endl;
        assert(dsaa::TestObject::livecount == 0);
    }
} verifier;
