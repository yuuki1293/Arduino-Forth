#ifndef MACRO_HPP
#define MACRO_HPP

#define _lw 0

#define native3(name, label, flag) \
    void (*i_##label)() = &label;  \
    word w_##label = {_lw,         \
                      name,        \
                      flag,        \
                      &i_##label}

#define native2(name, label) native3(name, label, 0)

#define native1(label) native2(#label, label)

#endif // MACRO_HPP