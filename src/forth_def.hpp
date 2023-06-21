#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

#include <stdlib.h>

union body
{
    body *inner;
    size_t value;
    void (*impl)();
};

struct word
{
    struct word *next;
    const char *name;
    bool flag;
    body xt;
};

#endif // FORTH_DEF_HPP