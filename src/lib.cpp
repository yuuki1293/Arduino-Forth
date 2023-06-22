#include "lib.hpp"

void print_int(intptr_t num)
{
#if defined(LOCAL)
    printf("%ld\n", num);
#else
    Serial.println(num);
#endif
}