#ifndef LIB_HPP
#define LIB_HPP

#include <stdint.h>
#include <string.h>

#if defined(LOCAL)
#include <stdio.h>
#else
#include <Arduino.h>
#endif

void print_int(intptr_t num);

void print_char(char c);

size_t read_str(char *buf);

void print_str(const char *cp);

#endif // LIB_HPP