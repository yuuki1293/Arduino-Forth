#include "global.hpp"

body *pc;
body w;
int32_t *stack;
body **rstack;

int32_t stack_start[256];
body *rstack_start[64];
char input_buf[64];
int32_t user_mem[256];
word dict_mem[64];

uint32_t state = 0;
word *here = dict_mem;