#include "global.hpp"

const body *pc;
const body *w;
intptr_t *stack;
const body **rstack;

intptr_t stack_start[FORTH_STACK_SIZE];
const body *rstack_start[FORTH_RSTACK_SIZE];
char input_buf[FORTH_INPUT_BUF];
intptr_t user_mem[FORTH_USER_MEM];
body dict_mem[FORTH_DICT_MEM];

forth_state state = forth_state::INTERPRETER;
body *here = dict_mem;