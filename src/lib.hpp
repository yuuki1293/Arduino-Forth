#ifndef LIB_HPP
#define LIB_HPP

#if defined(LOCAL)
#include <string.h>
#else
#include <Arduino.h>
#endif

void print_int(intptr_t num);

#endif // LIB_HPP