#include "words.hpp"

static body *program_stub = &w_main_stub.xt;

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

static void rpush(body *body)
{
    rstack++;
    *rstack = body;
    return;
}

static body *rpop()
{
    body *body = *rstack;
    rstack--;
    return body;
}

native1(init)
{
    stack = stack_start;
    rstack = rstack_start;
    pc = program_stub;
    state = 0;
    here = dict_mem;
    next();
}
#define _lw ref(init)

native1(docol)
{
    rpush(pc);
    w++;
    pc = w;
    next();
}
#define _lw ref(docol)

native1(exit)
{
    pc = rpop();
    next();
}
#define _lw ref(exit)

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

colon1(main_stub){
    impl(docol),
    lit(1), lit(2),
    w_swap.xt};

word *last_word = _lw;