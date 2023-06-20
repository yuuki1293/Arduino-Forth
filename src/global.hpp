#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>
#include "forth_def.hpp"

extern void (**pc)();
extern void (*w)();
extern int32_t* stack;

extern int32_t stack_start[1024];
extern char input_buf[256];
extern int32_t user_mem[1024];
extern word dict_mem[256];

extern void* stack_base;
extern uint8_t state;
extern void* here;

#endif //GLOBAL_HPP