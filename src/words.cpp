#include "words.hpp"

static void push(int32_t value)
{
    stack++;
    *stack = value;
    return;
}

static int32_t pop();

[[noreturn]] void drop()
{
    stack--;
    next();
}

native1(drop);
#define _lw w_drop