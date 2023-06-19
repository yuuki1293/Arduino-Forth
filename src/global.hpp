#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>

void (**pc)();
void (*w)();
void* stack;

void* stack_start[1024];
char input_buf[1024];
void* user_mem[65536];
void* dict_mem[65536];

void* last_word;
void* stack_base;
uint8_t state;
void* here = dict_mem;

#endif //GLOBAL_HPP