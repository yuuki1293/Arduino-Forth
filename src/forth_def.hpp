#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

union body
{
    void (*impl)();
    body *xt;
};

struct word
{
    struct word *next;
    char *name;
    bool flag;
    body xt;
};

#endif // FORTH_DEF_HPP