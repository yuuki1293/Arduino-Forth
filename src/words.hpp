#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>
#include "global.hpp"
#include "macro.hpp"
#include "next.hpp"

[[noreturn]] void i_init();

[[noreturn]] void i_docol();

[[noreturn]] void i_exit();

[[noreturn]] void i_drop();

[[noreturn]] void i_swap();

extern word *last_word;

#endif // WORDS_HPP