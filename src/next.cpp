#include "next.hpp"

[[noreturn]] void next()
{
    while (true)
    {
        w = pc->inner;
        pc++;
        w->impl_p();
    }
}