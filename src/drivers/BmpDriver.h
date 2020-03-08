#ifndef ATMEGA2560_BMPDRIVER_H
#define ATMEGA2560_BMPDRIVER_H

#include <SFE_BMP180.h>

class BmpDriver {
private:
    double pressure = 0;
    double temp = 0;
    SFE_BMP180 bmp;

public:
    BmpDriver();

    void begin();

    // returns true if measurement succeed
    boolean measurePressure();

    // return pressure, should be called after measurePressure()
    double getPressure();

    // return temperature, should be called after measurePressure()
    double getTemperature();

    // returns error code
    // 0 = Success
    // 1 = Data too long to fit in transmit buffer
    // 2 = Received NACK on transmit of address
    // 3 = Received NACK on transmit of data
    // 4 = Other error
    char getError();
};

#endif //ATMEGA2560_BMPDRIVER_H
