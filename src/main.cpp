#include "main.hpp"

void setup() {
    Serial.begin(9600);
    Serial.println(F("setup"));
    forth_init();
}

void loop() {
}