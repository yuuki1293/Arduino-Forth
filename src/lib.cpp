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

void read_str(char *buf)
{
#if defined(LOCAL)
    scanf("%s", buf);
#else
    size_t i = 0;
    char input = 1;

    while (Serial.available())
    {
        input = (char)Serial.read();
        buf[i] = input;
        i++;

        if (input == ' ' || input == '\n' || input == '\t' || input == '\0')
        {
            buf[i] = '\0';
            return;
        }
    }

    buf[i] = '\0';
#endif
    return;
}