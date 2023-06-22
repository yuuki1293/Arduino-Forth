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

/**
 * 最初に呼び出されるワード。
 */
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

/**
 * 全てのコロンワードの始まり。
 */
native1(docol)
{
    rpush(pc);
    w++;
    pc = w;
    next();
}
#undef _lw
#define _lw ref(docol)

/**
 * 全てのコロンワードの終わり。
 */
native1(exit)
{
    pc = rpop();
    next();
}
#undef _lw
#define _lw ref(exit)

/**
 * プログラムを正常終了させる。
 */
native1(bye)
{
    exit(0);
}
#undef _lw
#define _lw ref(bye)

/**
 * スタックから値を1つ捨てる。
 * ( a -- )
 */
native1(drop)
{
    stack--;
    next();
}
#undef _lw
#define _lw ref(drop)

/**
 * スタックの1番目と2番目を交換する。
 * ( x2 x1 -- x1 x2 )
 */
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

/**
 * スタックの値を複製する。
 * ( a - a a )
 */
native1(dup)
{
    int32_t a;
    a = pop();
    push(a);
    push(a);
    next();
}
#undef _lw
#define _lw ref(dup)

/**
 * スタックの1番目から3番目を回転させる。
 * ( x3 x2 x1 -- x2 x1 x3 )
 */
native1(rot)
{
    int32_t x1, x2, x3;
    x1 = pop();
    x2 = pop();
    x3 = pop();
    push(x2);
    push(x1);
    push(x3);
    next();
}

/**
 * スタックの1番目と2番目を足す。
 * ( nu2 nu1 -- [ nu1 + nu2 ] )
 */
native2("+", plus)
{
    int32_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 + x2);
    next();
}

/**
 * スタックの1番目から2番目を引く。
 * ( nu2 nu1 -- [ nu1 - nu2 ] )
 */
native2("-", minus)
{
    int32_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 - x2);
    next();
}

/**
 * スタックの1番目と2番目を掛ける
 * ( nu2 nu1 -- [ nu1 * nu2 ] )
 */
native2("*", mul)
{
    int32_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 * x2);
    next();
}

/**
 * スタックの1番目を2番目で割る。
 * ( nu2 nu1 -- [ nu1 / nu2 ] )
 */
native2("/", div)
{
    int32_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 / x2);
    next();
}

/**
 * スタックの値の論理否定を取る。
 * ( x = !x )
 */
native1(not )
{
    int32_t x;
    x = pop();
    push(!x);
    next();
}

/**
 * スタックの1番目と2番目が等しいか比較する。
 * ( nu1 nu2 -- [ nu1 = nu2 ] )
 */
native2("=", eq)
{
    int32_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 == x2);
    next();
}

/**
 * メインワード。
 */
colon1(main_stub){
    impl(docol),
    xt(bye)};
#undef _lw
#define _lw ref(main_stub)

word *last_word = _lw;

/**
 * @brief 最初に呼び出されるワードを呼び出す。
 */
[[noreturn]] void init()
{
    i_init();
}