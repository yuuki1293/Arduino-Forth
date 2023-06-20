#ifndef MACRO_HPP
#define MACRO_HPP

#define _lw 0

#define ref(f) &w_##f

#define impl(f)        \
    {                  \
        .impl = &i_##f \
    }

#define lit(a)     \
    {              \
        .value = a \
    }

#define native3(name, label, flag)           \
    word w_##label = {_lw,                   \
                      name,                  \
                      flag,                  \
                      {.impl = &i_##label}}; \
    [[noreturn]] void i_##label()

#define native2(name, label) native3(name, label, 0)

#define native1(label) native2(#label, label)

#define colon3(name, label, flag) \
    body a_##label[];             \
    word w_##label = {_lw,        \
                      name,       \
                      flag,       \
                      a_##label}; \
    body a_##label[] =

#define colon2(name, label) colon3(name, label, 0)

#define colon1(label) colon2(#label, label)

#endif // MACRO_HPP