#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>
#include "forth_def.hpp"

void (**pc)();
void (*w)();
int32_t** stack;

int32_t* stack_start[1024];
char input_buf[256];
int32_t* user_mem[1024];
word* dict_mem[256];

#endif //GLOBAL_HPP