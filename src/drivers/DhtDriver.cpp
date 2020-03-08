#include "DhtDriver.h"


DhtDriver::DhtDriver(uint8_t pin, uint8_t type) {
    this->dht = DHT(pin, type);
}

void DhtDriver::begin() {
    this->dht.begin();
}

float DhtDriver::readHumidity() {
    return this->dht.readHumidity();
}

float DhtDriver::readTemperature() {
    return this->dht.readTemperature();
}

