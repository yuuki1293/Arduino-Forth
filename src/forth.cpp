#include "forth.hpp"

void (**pc)();
void (*w)();
void* stack;

void* stack_start[1024];
char input_buf[1024];
void* user_mem[65536];
void* dict_mem[65536];

void* last_word;
void* stack_base = 0;
uint8_t state = 0;
void* here = dict_mem;

void next(){
    w = *pc;
    pc++;
    w();
}