#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>
#include "global.hpp"
#include "macro.hpp"
#include "next.hpp"

static void push(int32_t value);
static int32_t pop();

[[noreturn]] void drop();

extern word *last_word;

#endif // WORDS_HPP