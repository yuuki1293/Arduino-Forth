#include "lib.hpp"

void print_int(intptr_t num)
{
#if defined(LOCAL)
    printf("%ld\n", (long)num);
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

size_t read_str(char *buf)
{
#if defined(LOCAL)
    if (!scanf("%s", buf))
        return 0;
    return strlen(buf);
#else
    size_t i = 0;
    char input;

    while (true)
    {
        while (!Serial.available())
        {
        }

        input = (char)Serial.read();
        buf[i] = input;

        Serial.print(input);

        if (isspace(input))
        {
            break;
        }

        i++;
    }

    Serial.println();

    buf[i] = '\0';
    return i;
#endif
}

void print_str(const char *cp)
{
#if defined(LOCAL)
    printf("%s\n", cp);
#else
    Serial.println(cp);
#endif
}