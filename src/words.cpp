#include "words.hpp"

extern forth_word w_main_stub;
static body program_stub = {.inner = w_main_stub.xt};

/**
 * @brief スタックに値をプッシュする。
 *
 * @param value 値
 */
static void push(intptr_t value)
{
    stack++;
    *stack = value;
    return;
}

/**
 * @brief スタックから値をポップする。
 *
 * @return intptr_t 値
 */
static intptr_t pop()
{
    intptr_t value = *stack;
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
#if !defined(LOCAL)
    Serial.flush();
#endif
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
    intptr_t a, b;
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
    intptr_t a;
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
    intptr_t x1, x2, x3;
    x1 = pop();
    x2 = pop();
    x3 = pop();
    push(x2);
    push(x1);
    push(x3);
    next();
}
#undef _lw
#define _lw ref(rot)

/**
 * スタックの1番目と2番目を足す。
 * ( nu2 nu1 -- [ nu1 + nu2 ] )
 */
native2("+", plus)
{
    intptr_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 + x2);
    next();
}
#undef _lw
#define _lw ref(plus)

/**
 * スタックの1番目から2番目を引く。
 * ( nu2 nu1 -- [ nu1 - nu2 ] )
 */
native2("-", minus)
{
    intptr_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 - x2);
    next();
}
#undef _lw
#define _lw ref(minus)

/**
 * スタックの1番目と2番目を掛ける
 * ( nu2 nu1 -- [ nu1 * nu2 ] )
 */
native2("*", mul)
{
    intptr_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 * x2);
    next();
}
#undef _lw
#define _lw ref(mul)

/**
 * スタックの1番目を2番目で割る。
 * ( nu2 nu1 -- [ nu1 / nu2 ] )
 */
native2("/", div)
{
    intptr_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 / x2);
    next();
}
#undef _lw
#define _lw ref(div)

/**
 * スタックの値の論理否定を取る。
 * ( x = !x )
 */
native1(not )
{
    intptr_t x;
    x = pop();
    push(!x);
    next();
}
#undef _lw
#define _lw ref(not )

/**
 * スタックの1番目と2番目が等しいか比較する。
 * ( nu1 nu2 -- [ nu1 = nu2 ] )
 */
native2("=", eq)
{
    intptr_t x1, x2;
    x1 = pop();
    x2 = pop();
    push(x1 == x2);
    next();
}
#undef _lw
#define _lw ref(eq)

/**
 * スタックの文字列へのポインタの長さを返す。
 * ( str -- len )
 */
native1(count)
{
    char *cp;
    cp = (char *)pop();
    push(strlen(cp));
    next();
}
#undef _lw
#define _lw ref(count)

/**
 * スタックの数をプリントする。
 * ( nu -- )
 */
native2(".", dot)
{
    intptr_t x;
    x = pop();
    print_int(x);
    next();
}
#undef _lw
#define _lw ref(dot)

/**
 * スタックの数を全てプリントする。スタックは消費されない。
 */
native2(".s", show_stack)
{
    for (intptr_t *i = stack; i > stack_start; i--)
    {
        print_int(*i);
    }

    next();
}
#undef _lw
#define _lw ref(show_stack)

/**
 * データスタックのアドレスをリターンスタックにプッシュする。
 * ( x -- )
 */
native2(">r", push_r)
{
    body *x;
    x = (body *)pop();
    rpush(x);
    next();
}
#undef _lw
#define _lw ref(push_r)

/**
 * リターンスタックのアドレスをデータスタックにプッシュする。
 * ( -- x )
 */
native2("r>", pop_r)
{
    body *x;
    x = rpop();
    push((intptr_t)x);
    next();
}
#undef _lw
#define _lw ref(pop_r)

/**
 * リターンスタックのアドレスをデータスタックにプッシュする。リターンスタックは消費されない。
 * ( -- x )
 */
native2("r@", fetch_r)
{
    push((intptr_t)*rstack);
    next();
}
#undef _lw
#define _lw ref(fetch_r)

/**
 * 文字列へのポインタから、そのワードヘッダへのポインタをプッシュする。
 * もし、その名前のワードがなければ0をプッシュする。
 * ( str -- addr )
 */
native1(find)
{
    char *x;
    forth_word *word_p;

    x = (char *)pop();
    word_p = last_word;

    while (!word_p)
    {
        if (strcmp(x, word_p->name))
        {
            push((intptr_t)word_p);
            next();
        }

        word_p = word_p->next;
    }

    push(0);
    next();
}
#undef _lw
#define _lw ref(find)

/**
 * ワードへのポインタから、実行トークンのアドレスをプッシュする。
 * ( addr -- addr )
 */
native1(cfa)
{
    forth_word *x;
    x = (forth_word *)pop();
    push((intptr_t)x->xt);
    next();
}
#undef _lw
#define _lw ref(cfa)

/**
 * スタックの文字をプリントする。
 * ( c -- )
 */
native1(emit)
{
    char c;
    c = (char)pop();
    print_char(c);
    next();
}
#undef _lw
#define _lw ref(emit)

/**
 * 文字列を読み取り、スタックのアドレスに格納する。
 * 文字列の長さをスタックにプッシュする。
 * ( addr -- length )
 */
native1(word)
{
    intptr_t len;
    char *buf;
    buf = (char *)pop();
    len = read_str(buf);
    push(len);
    next();
}
#undef _lw
#define _lw ref(word)

/**
 * スタックのポインタの文字列を符号付き整数に変換する。変換後の整数と変換した文字列の長さをスタックにプッシュする。
 * ( str -- nu length)
 */
native1(number)
{
    char *cp;
    char *endptr;
    intptr_t num, leng;

    cp = (char *)pop();

    num = strtol(cp, &endptr, 0);
    leng = strlen(cp);

    if (strlen(endptr))
    {
        leng = 0;
    }

    push(num);
    push(leng);
    next();
}
#undef _lw
#define _lw ref(number)

/**
 * スタックのポインタの文字列をプリントする。
 * ( str -- )
 */
native1(prints)
{
    char *cp;
    cp = (char *)pop();
    print_str(cp);
    next();
}
#undef _lw
#define _lw ref(prints)

/**
 * 次の命令の数値だけ命令をスキップする。
 * コンパイルモードのみ！
 */
native1(branch)
{
    pc += pc->value;
    pc++;
    next();
}
#undef _lw
#define _lw ref(branch)

/**
 * スタックの値が0の場合、次の命令の数値だけ命令をスキップする。
 * コンパイルモードのみ！
 * ( x -- )
 */
native2("0branch", branch0)
{
    bool flag;
    flag = pop();

    if (!flag)
        pc += pc->value;
    pc++;

    next();
}
#undef _lw
#define _lw ref(branch0)

/**
 * 次の命令の数値をスタックヘプッシュする。
 * ( -- a )
 */
native1(lit)
{
    push(pc->value);
    pc++;
    next();
}
#undef _lw
#define _lw ref(lit)

/**
 * インプットバッファのアドレスをスタックにプッシュする。
 * ( -- addr )
 */
native1(inbuf)
{
    push((intptr_t)input_buf);
    next();
}
#undef _lw
#define _lw ref(inbuf)

/**
 * ユーザーメモリの開始アドレスをスタックにプッシュする。
 * ( -- addr )
 */
native1(mem)
{
    push((intptr_t)user_mem);
    next();
}
#undef _lw
#define _lw ref(mem)

/**
 * メインワード。
 */
colon1(main_stub){
    impl(docol),
    lit(1), lit(2),
    xt(show_stack),
    xt(plus),
    xt(show_stack),
    xt(bye)};
#undef _lw
#define _lw ref(main_stub)

forth_word *last_word = _lw;

/**
 * @brief 最初に呼び出されるワードを呼び出す。
 */
[[noreturn]] void forth_init()
{
    i_init();
}