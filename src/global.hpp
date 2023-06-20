#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>
#include "forth_def.hpp"

extern body *pc;
extern body w;
extern int32_t *stack;
extern body **rstack;

extern int32_t stack_start[1024];
extern body *rstack_start[64];
extern char input_buf[256];
extern int32_t user_mem[1024];
extern word dict_mem[256];

extern uint32_t state;
extern word *here;

#endif // GLOBAL_HPP