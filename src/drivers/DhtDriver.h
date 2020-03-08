#ifndef ATMEGA2560_DHTDRIVER_H
#define ATMEGA2560_DHTDRIVER_H

#include <DHT.h>

class DhtDriver {
    DHT dht = DHT(0, 0);
public:
    DhtDriver(uint8_t pin, uint8_t type = DHT22);

    void begin();

    float readHumidity();

    float readTemperature();
};

#endif //ATMEGA2560_DHTDRIVER_H
