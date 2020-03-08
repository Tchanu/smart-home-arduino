#include <Arduino.h>
#include "MQ135Driver.h"

MQ135Driver::MQ135Driver(uint8_t pin) {
    this->pin = pin;
}

int MQ135Driver::read() {
    return analogRead(this->pin);
}