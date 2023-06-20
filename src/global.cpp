#include "global.hpp"

void (**pc)();
void (*w)();
int32_t** stack;

int32_t* stack_start[1024];
char input_buf[1024];
void* user_mem[65536];
word* dict_mem[65536];