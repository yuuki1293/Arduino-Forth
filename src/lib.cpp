#include "lib.hpp"

void print_int(intptr_t num)
{
#if defined(LOCAL)
    printf("%ld", num);
#else
    Serial.println(num);
#endif
}