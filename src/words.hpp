#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>
#include <string.h>

#if !defined(LOCAL)
#include <Arduino.h>
#endif

#include "global.hpp"
#include "lib.hpp"
#include "macro.hpp"
#include "next.hpp"

extern forth_word *last_word;

[[noreturn]] void forth_init();

#endif // WORDS_HPP