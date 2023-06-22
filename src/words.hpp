#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>
#include "global.hpp"
#include "macro.hpp"
#include "next.hpp"

extern word *last_word;

[[noreturn]] void init();

#endif // WORDS_HPP