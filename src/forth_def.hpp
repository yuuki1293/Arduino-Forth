#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

#include <stdlib.h>

union body
{
    body *inner;
    size_t value;
    void (*impl_p)() __attribute__((noreturn));
};

struct forth_word
{
    struct forth_word *next;
    const char *name;
    bool flag;
    body *xt;
};

enum class forth_state : intptr_t
{
    INTERPRETER,
    COMPILER
};

#endif // FORTH_DEF_HPP