#ifndef WORDS_HPP
#define WORDS_HPP

#include <stdint.h>

#if !defined(LOCAL)
#include <Arduino.h>
#endif

#include "global.hpp"
#include "macro.hpp"
#include "next.hpp"

extern forth_word *last_word;

[[noreturn]] void init();

#endif // WORDS_HPP