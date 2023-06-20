#include "words.hpp"

static void (**program_stub)();

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

static void rpush(void (**f)())
{
    rstack++;
    *rstack = f;
    return;
}

static void (**rpop())()
{
    void (**f)() = *rstack;
    rstack--;
    return f;
}

native1(init)
{
    stack = stack_start;
    rstack = rstack_start;
    pc = (void **)program_stub;
    state = 0;
    here = dict_mem;
    next();
}
#define _lw ref(init)

native1(docol)
{
    rpush((void (**)())pc);
    w++;
    pc = w;
    next();
}
#define _lw ref(docol)

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

colon1(main_stub){(int8_t)&i_docol, 1, 2, (int8_t)w_swap.xt};

word *last_word = _lw;