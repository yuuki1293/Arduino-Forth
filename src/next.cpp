#include "next.hpp"

[[noreturn]] void next()
{
    w = *pc;
    pc++;
    w();
}