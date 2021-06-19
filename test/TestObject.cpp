#include "TestObject.h"

struct verify
{
    ~verify()
    {
        assert(dsaa::TestObject::livecount == 0);
    }
} verifier;
