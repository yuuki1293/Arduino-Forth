#include "next.hpp"

void next()
{
    w = *pc;
    pc++;
    w();
}