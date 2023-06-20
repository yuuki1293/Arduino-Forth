#include "global.hpp"

body *pc;
body w;
int32_t *stack;
body **rstack;

int32_t stack_start[FORTH_STACK_SIZE];
body *rstack_start[FORTH_RSTACK_SIZE];
char input_buf[FORTH_INPUT_BUF];
int32_t user_mem[FORTH_USER_MEM];
word dict_mem[FORTH_DICT_MEM];

uint32_t state = 0;
word *here = dict_mem;