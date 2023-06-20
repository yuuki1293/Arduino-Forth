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

native1(drop)
{
    stack--;
    next();
}
#define _lw ref(drop)

word *last_word = _lw;