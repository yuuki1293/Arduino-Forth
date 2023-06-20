#include "next.hpp"

[[noreturn]] void next()
{
    w = (*pc).xt;
    pc++;
    w->impl();
}