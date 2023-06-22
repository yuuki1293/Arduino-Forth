#include "words.hpp"

extern word w_main_stub;
static body program_stub = {.inner = w_main_stub.xt};

/**
 * @brief スタックに値をプッシュする。
 * 
 * @param value 値
 */
static void push(int32_t value)
{
    stack++;
    *stack = value;
    return;
}

/**
 * @brief スタックから値をポップする。
 * 
 * @return int32_t 値
 */
static int32_t pop()
{
    int32_t value = *stack;
    stack--;
    return value;
}

/**
 * @brief リターンスタックにアドレスをプッシュする。
 * 
 * @param body アドレス
 */
static void rpush(body *body)
{
    rstack++;
    *rstack = body;
    return;
}

/**
 * @brief リターンスタックからアドレスをポップする。
 * 
 * @return body* アドレス
 */
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
    pc = &program_stub;
    state = 0;
    here = dict_mem;
    next();
}
#undef _lw
#define _lw ref(init)

native1(docol)
{
    rpush(pc);
    w++;
    pc = w;
    next();
}
#undef _lw
#define _lw ref(docol)

native1(exit)
{
    pc = rpop();
    next();
}
#undef _lw
#define _lw ref(exit)

native1(bye)
{
    exit(0);
}
#undef _lw
#define _lw ref(bye)

native1(drop)
{
    stack--;
    next();
}
#undef _lw
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
#undef _lw
#define _lw ref(swap)

colon1(main_stub){
    impl(docol),
    xt(bye)};
#undef _lw
#define _lw ref(main_stub)

word *last_word = _lw;

[[noreturn]] void init()
{
    i_init();
}