#include "global.hpp"

void (**pc)();
void (*w)();
int32_t* stack;

int32_t stack_start[1024];
char input_buf[256];
int32_t user_mem[1024];
word dict_mem[256];

void* stack_base = 0;
uint8_t state = 0;
void* here = dict_mem;