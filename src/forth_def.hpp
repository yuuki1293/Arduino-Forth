#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

union body
{
    body *xt;
    int8_t value;
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