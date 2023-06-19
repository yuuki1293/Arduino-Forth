#include "forth.hpp"

void next(){
    w = *pc;
    pc++;
    w();
}