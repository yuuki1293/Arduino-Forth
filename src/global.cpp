#include "global.hpp"

void **pc;
void **w;
int32_t *stack;
void (***rstack)();

int32_t stack_start[1024];
void (**rstack_start[64])();
char input_buf[256];
int32_t user_mem[1024];
word dict_mem[256];

uint32_t state = 0;
word *here = dict_mem;