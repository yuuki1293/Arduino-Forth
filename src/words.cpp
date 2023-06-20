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

native1(init)
{
    stack = stack_start;
    pc = w_stub.xt;
    state = 0;
    here = dict_mem;
    next();
}
#define _lw ref(init)

native1(drop)
{
    stack--;
    next();
}
#define _lw ref(drop)

native1(swap)
{
    int32_t a, b;
    a = pop();
    b = pop();
    push(a);
    push(b);
    next();
}
#define _lw ref(swap)

word *last_word = _lw;