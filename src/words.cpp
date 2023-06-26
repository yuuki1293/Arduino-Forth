#include "words.hpp"

extern const forth_word w_main_stub;
static const body program_stub = {.inner = w_main_stub.xt};

/**
 * 最初に呼び出されるワード。
 */
native1(init)
{
    stack = stack_start;
    rstack = rstack_start;
    pc = &program_stub;
    state = forth_state::INTERPRETER;
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
#define docol_impl impl(docol)
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
    print_str("bye.");
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
    const body *x;
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
    const forth_word *word_p;

    x = (char *)pop();
    word_p = last_word;

    while (word_p)
    {
        if (!strcmp(x, word_p->name))
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
    forth_word *fwp;
    fwp = (forth_word *)pop();
    push((intptr_t)fwp->xt);
    next();
}
#undef _lw
#define _lw ref(cfa)

/**
 * ワードへのポインタから、フラグをプッシュする。
 * ( addr -- flag )
 */
native1(flag)
{
    forth_word *fwp;
    fwp = (forth_word *)pop();
    push((intptr_t)fwp->flag);
    next();
}
#undef _lw
#define _lw ref(flag)

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
const2(inbuf, input_buf);
#undef _lw
#define _lw ref(inbuf)

/**
 * ユーザーメモリのアドレスをスタックにプッシュする。
 * ( -- addr )
 */
const2(mem, user_mem);
#undef _lw
#define _lw ref(mem)

/**
 * last_wordをスタックにプッシュする。
 * ( -- addr )
 */
const1(last_word);
#undef _lw
#define _lw ref(last_word)

/**
 * stateをスタックにプッシュする。
 * ( -- addr )
 */
const2(state, &state);
#undef _lw
#define _lw ref(state)

/**
 * 辞書メモリの空き先頭アドレスをスタックにプッシュする。
 * ( -- addr )
 */
const2(here, &here);
#undef _lw
#define _lw ref(here)

/**
 * スタックの実行トークンを実行する。
 * ( xt -- )
 */
native1(execute)
{
    w = (body *)pop();
    w->impl_p();
}
#undef _lw
#define _lw ref(execute)

/**
 * スタックのアドレスをデリファレンスする。
 * ( addr -- data )
 */
native2("@", fetch)
{
    intptr_t *x;
    x = (intptr_t *)pop();
    push(*x);
    next();
}
#undef _lw
#define _lw ref(fetch)

/**
 * スタックの1番目の値を2番目のアドレスに書き込む。
 * ( addr data -- )
 */
native2("!", write)
{
    intptr_t x, *p;
    x = pop();
    p = (intptr_t *)pop();
    *p = x;
    next();
}
#undef _lw
#define _lw ref(write)

/**
 * スタックのトップの文字へのアドレスをとしてデリファレンスする。
 * ( addr -- c )
 */
native2("@c", fetch_c)
{
    char *cp;
    cp = (char *)pop();
    push(*cp);
    next();
}
#undef _lw
#define _lw ref(fetch_c)

/**
 * スタックの実行トークンを定義中のワードに追加する。
 * ( xt -- )
 */
native2(",", comma)
{
    body *xt;
    xt = (body *)pop();
    here->inner = xt;
    here++;
    next();
}
#undef _lw
#define _lw ref(comma)

/**
 * スタックの文字を定義中のワードに追加する。
 * ( c -- )
 */
native2("c,", comma_c)
{
    char c;
    c = (char)pop();
    here->value = c;
    here++;
    next();
}
#undef _lw
#define _lw ref(comma_c)

/**
 * 辞書に新しい名前を持つエントリを作成する。
 * ( flags name -- )
 */
native1(create)
{
    char *name, *new_name;
    bool flag;
    forth_word *new_word;
    name = (char *)pop();
    flag = (bool)pop();

    new_word = (forth_word *)malloc(sizeof(forth_word));
    new_word->next = last_word;
    last_word = new_word;
    new_name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy(new_name, name);
    new_word->name = new_name;
    new_word->flag = flag;
    new_word->xt = here;

    next();
}
#undef _lw
#define _lw ref(create)

/**
 * 入力からワードを読み、その定義を開始する。
 */
colon2(":", colon){
    docol_impl,
    xt(inbuf), xt(word), xt(drop),
    lit(0), xt(inbuf),
    xt(create),
    xt(lit), impl(docol), xt(comma),
    xt(state), lit(1), xt(write),
    xt(exit)};
#undef _lw
#define _lw ref(colon)

/**
 * ワードの定義を終わる。
 */
colon3(";", semicolon, 1){
    docol_impl,
    xt(lit), xt(exit), xt(comma),
    xt(state), lit(0), xt(write),
    xt(exit)};
#undef _lw
#define _lw ref(semicolon)

/**
 * コンパイラ&インタープリター
 */
colon1(main_stub){
    docol_impl,
    /* start 22 */
    // 4
    xt(inbuf),
    xt(word),
    branch0(78 /* exit */),

    // 4
    xt(state),
    xt(fetch_c),
    branch0(51 /* interpreter */),

    // 5
    xt(inbuf),
    xt(find),
    xt(dup),
    branch0(12 /* c_num */),

    // 6
    xt(dup),
    xt(cfa),
    xt(swap),
    xt(flag),
    branch0(3 /* comma */),

    // 3
    xt(execute),
    branch(-22 /* start */),

    /* comma 3 */
    // 3
    xt(comma),
    branch(-25 /* start */),

    /* c_num 34 */
    // 5
    xt(drop),
    xt(inbuf),
    xt(number),
    branch0(46 /* not found */),

    // 12
    lit(CELL_SIZE),
    xt(here),
    xt(fetch),
    xt(minus),
    xt(fetch),
    xt(lit),
    xt(branch),
    xt(eq),
    xt(not ),
    branch0(-20 /* comma */),

    // 12
    lit(CELL_SIZE),
    xt(here),
    xt(fetch),
    xt(minus),
    xt(fetch),
    xt(lit),
    xt(branch0),
    xt(eq),
    xt(not ),
    branch0(-32 /* comma */),

    // 5
    xt(lit),
    xt(lit),
    xt(comma),
    branch(-37 /* comma */),

    /* interpreter 9 */
    // 5
    xt(inbuf),
    xt(find),
    xt(dup),
    branch0(4 /* i_num */),

    // 4
    xt(cfa),
    xt(execute),
    branch(-68 /* start */),

    /* i_num 7 */
    // 5
    xt(drop),
    xt(inbuf),
    xt(number),
    branch0(2 /* not found */),

    // 2
    branch(-75 /* start */),

    /* not found 6 */
    // 6
    xt(drop),
    xt(lit),
    {.value = (intptr_t) "no such word."},
    xt(prints),
    branch(-81 /* start */),

    /* exit 2*/
    // 2
    xt(bye),
    xt(exit)};
#undef _lw
#define _lw ref(main_stub)

const forth_word *last_word = _lw;

/**
 * @brief 最初に呼び出されるワードを呼び出す。
 */
[[noreturn]] void forth_init()
{
    i_init();
}