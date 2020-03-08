#ifndef ATMEGA2560_MQ135DRIVER_H
#define ATMEGA2560_MQ135DRIVER_H

#include <Arduino.h>

class MQ135Driver {
    uint8_t pin = 0;
public:
    MQ135Driver(uint8_t pin);

    int read();
};

#endif //ATMEGA2560_MQ135DRIVER_H
