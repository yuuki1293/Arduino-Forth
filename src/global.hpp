#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdio.h>
#include <stdint.h>
#include "forth_def.hpp"

#define FORTH_STACK_SIZE 64
#define FORTH_RSTACK_SIZE 16
#define FORTH_INPUT_BUF 100
#define FORTH_USER_MEM 64
#define FORTH_DICT_MEM 64

#define CELL_SIZE sizeof(intptr_t)

extern const body *pc;
extern const body *w;
extern intptr_t *stack;
extern const body **rstack;

extern intptr_t stack_start[FORTH_STACK_SIZE];
extern const body *rstack_start[FORTH_RSTACK_SIZE];
extern char input_buf[FORTH_INPUT_BUF];
extern intptr_t user_mem[FORTH_USER_MEM];
extern body dict_mem[FORTH_DICT_MEM];

extern forth_state state;
extern body *here;

/**
 * @brief スタックに値をプッシュする。
 *
 * @param value 値
 */
void push(intptr_t value);

/**
 * @brief スタックから値をポップする。
 *
 * @return intptr_t 値
 */
intptr_t pop();

/**
 * @brief リターンスタックにアドレスをプッシュする。
 *
 * @param body アドレス
 */
void rpush(const body *body);

/**
 * @brief リターンスタックからアドレスをポップする。
 *
 * @return body* アドレス
 */
const body *rpop();

#endif // GLOBAL_HPP