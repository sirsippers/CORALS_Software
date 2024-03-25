#include <Arduino.h>

#include <CORALS.hpp>

void setup() {
    CORALS::initialize();
}

void loop() {
    CORALS::run();
}