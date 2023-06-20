#include "forth.hpp"

word* last_word = _lw;
void* stack_base = 0;
uint8_t state = 0;
void* here = dict_mem;