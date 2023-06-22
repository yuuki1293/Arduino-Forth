#ifndef MACRO_HPP
#define MACRO_HPP

#define _lw 0

#define ref(f) &w_##f

#define xt(w) w_##w.xt

#define impl(f)        \
    {                  \
        .impl = &i_##f \
    }

#define lit(a)     \
    xt(lit),       \
    {              \
        .value = a \
    }

#define native3(name, label, flag)            \
    [[noreturn]] void i_##label();            \
    body a_##label[] = {{.impl = i_##label}}; \
    forth_word w_##label = {_lw,                    \
                      name,                   \
                      flag,                   \
                      a_##label};             \
    [[noreturn]] void i_##label()

#define native2(name, label) native3(name, label, 0)

#define native1(label) native2(#label, label)

#define colon3(name, label, flag) \
    extern body a_##label[];      \
    forth_word w_##label = {_lw,        \
                      name,       \
                      flag,       \
                      a_##label}; \
    body a_##label[] =

#define colon2(name, label) colon3(name, label, 0)

#define colon1(label) colon2(#label, label)

#endif // MACRO_HPP