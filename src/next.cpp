#include "next.hpp"

[[noreturn]] void next()
{
    w = (void **)*pc;
    pc++;
    (*((void (**)())w))();
}