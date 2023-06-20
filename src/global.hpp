#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>
#include "forth_def.hpp"

extern void **pc;
extern void **w;
extern int32_t* stack;
void (***rstack)();

extern int32_t stack_start[1024];
extern void (**rstack_start[64])();
extern char input_buf[256];
extern int32_t user_mem[1024];
extern word dict_mem[256];

extern uint32_t state;
extern word* here;

#endif //GLOBAL_HPP