#ifndef LIB_HPP
#define LIB_HPP

#include <stdint.h>
#include <stdio.h>

#if defined(LOCAL)
#include <string.h>
#else
#include <Arduino.h>
#endif

void print_int(intptr_t num);

void print_char(char c);

#endif // LIB_HPP