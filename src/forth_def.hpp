#ifndef FORTH_DEF_HPP
#define FORTH_DEF_HPP

struct word
{
    struct word *next;
    char *name;
    bool flag;
    void (**xt)();
};

#endif // FORTH_DEF_HPP