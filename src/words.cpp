#include "words.hpp"

static void push(int32_t value)
{
    stack++;
    *stack = value;
    return;
}

static int32_t pop()
{
    int32_t value = *stack;
    stack--;
    return value;
}

[[noreturn]] void drop()
{
    stack--;
    next();
}

native1(drop);
#define _lw w_drop