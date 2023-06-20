#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>
#include "global.hpp"
#include "macro.hpp"
#include "next.hpp"

static void push(int32_t value);
static int32_t pop();
static void rpush(void (**f)());
static void (**rpop())();

[[noreturn]] void init();

[[noreturn]] void docol();

[[noreturn]] void drop();

[[noreturn]] void swap();

extern word *last_word;

#endif // WORDS_HPP