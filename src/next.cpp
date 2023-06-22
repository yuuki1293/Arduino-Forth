#include "next.hpp"

[[noreturn]] void next()
{
    w = pc->inner;
    pc++;
    w->impl();
}