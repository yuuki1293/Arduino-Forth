#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdio.h>
#include <stdint.h>
#include "forth_def.hpp"

#define FORTH_STACK_SIZE 256
#define FORTH_RSTACK_SIZE 64
#define FORTH_INPUT_BUF 256
#define FORTH_USER_MEM 256
#define FORTH_DICT_MEM 64

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

#endif // GLOBAL_HPP