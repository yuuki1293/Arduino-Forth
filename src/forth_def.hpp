#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

#include <stdlib.h>

union body
{
    body *xt;
    size_t value;
    void (*impl)();
};

struct word
{
    struct word *next;
    char *name;
    bool flag;
    body xt;
};

#endif // FORTH_DEF_HPP