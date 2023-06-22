#include "lib.hpp"

void print_int(intptr_t num)
{
#if defined(LOCAL)
    printf("%ld\n", num);
#else
    Serial.println(num);
#endif
}

void print_char(char c)
{
#if defined(LOCAL)
    putchar(c);
#else
    Serial.println(c);
#endif
}