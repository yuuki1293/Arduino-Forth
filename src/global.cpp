#include "global.hpp"

body *pc;
body *w;
intptr_t *stack;
body **rstack;

intptr_t stack_start[FORTH_STACK_SIZE];
body *rstack_start[FORTH_RSTACK_SIZE];
char input_buf[FORTH_INPUT_BUF];
intptr_t user_mem[FORTH_USER_MEM];
forth_word dict_mem[FORTH_DICT_MEM];

uint32_t state = 0;
forth_word *here = dict_mem;