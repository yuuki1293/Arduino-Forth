#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>
#include "forth_def.hpp"

extern body *pc;
extern body w;
extern int32_t *stack;
extern body **rstack;

extern int32_t stack_start[256];
extern body *rstack_start[64];
extern char input_buf[64];
extern int32_t user_mem[256];
extern word dict_mem[64];

extern uint32_t state;
extern word *here;

#endif // GLOBAL_HPP