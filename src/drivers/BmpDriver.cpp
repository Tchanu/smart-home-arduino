#include <SFE_BMP180.h>
#include <drivers/BmpDriver.h>

// 0 to 3, higher numbers are slower, higher-res outputs.
const char BMP_OVERSAMPLING = 3;

BmpDriver::BmpDriver() {
    this->bmp = SFE_BMP180();
};

void BmpDriver::begin() {
    this->bmp.begin();
}

boolean BmpDriver::measurePressure() {
    char status;
    double T, P;

    // will return delay in ms to wait, or 0 if I2C error
    status = this->bmp.startTemperature();
    if (status == 0) return false;

    // wait for temp measurement
    delay(status);

    status = this->bmp.getTemperature(T);
    if (status == 0) return false;

    // will return delay in ms to wait, or 0 if I2C error.
    status = this->bmp.startPressure(BMP_OVERSAMPLING);
    if (status == 0) return false;

    // wait for pressure measurement
    delay(status);

    status = this->bmp.getPressure(P, T);
    if (status == 0) return false;

    //
    this->pressure = P;
    this->temp = T;
    return true;
}

double BmpDriver::getPressure() {
    return this->pressure;
}

double BmpDriver::getTemperature() {
    return this->temp;
}

char BmpDriver::getError() {
    return this->bmp.getError();
}
