#include <Arduino.h>
#include <DHT.h>
#include <SFE_BMP180.h>

int readMq135(uint8_t pin);

void handle_serial(int bytes);

enum Command {
    MQ135 = 'A',
    Dht = 'B',
    Bmp180 = 'C',
};


void send(Command command, String data);

const String RESPONSE_PREFIX = "^";
const String COMMAND_SUFFIX = "&";
const String RESPONSE_SUFFIX = "$";
const String DATA_SEPARATOR = "|";
const uint8_t MQ135_PIN = 0; // A0
const uint8_t DHT_PIN = 2; // D2
class DhtDriver {
    DHT dht;
public:
    DhtDriver(DHT dht) : dht(dht) {
    }

    void begin() {
        this->dht.begin();
    }

    float readHumidity() {
        return this->dht.readHumidity();
    }

    float readTemperature() {
        return this->dht.readTemperature();
    }
};

// 0 to 3, higher numbers are slower, higher-res outputs.
const char BMP_OVERSAMPLING = 3;

class BmpDriver {
    double pressure = 0;
    double temp = 0;
    SFE_BMP180 bmp;
public:
    BmpDriver(SFE_BMP180 bmp) : bmp(bmp) {
    }

    void begin() {
        this->bmp.begin();
    }

    /**
     *
     * @returns true if measurement succeed
     */
    boolean measurePressure() {
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

    /**
     * @description
     * should be called after measurePressure()
     * @returns pressure
     */
    double getPressure() {
        return this->pressure;
    }

    /**
     * @description
     * should be called after measurePressure()
     * @returns pressure
     */
    double getTemperature() {
        return this->temp;
    }

    // 0 = Success
    // 1 = Data too long to fit in transmit buffer
    // 2 = Received NACK on transmit of address
    // 3 = Received NACK on transmit of data
    // 4 = Other error
    char getError() {
        this->bmp.getError();
    }
};


auto dhtDriver = new DhtDriver(DHT(DHT_PIN, DHT22));
auto bmpDriver = new BmpDriver(SFE_BMP180());

void setup() {
    Serial.begin(9600);
    dhtDriver->begin();
    bmpDriver->begin();
}


void loop() {
    if (Serial.available() > 0) {
        handle_serial(Serial.read());
    }
}


void handle_serial(int byte) {
    const auto command = (Command) byte;

    switch (command) {
        case MQ135: {
            const int air_quality = readMq135(MQ135_PIN);
            send(command, (String) air_quality);
            break;
        }
        case Dht: {
            const float temp = dhtDriver->readTemperature();
            const float humidity = dhtDriver->readHumidity();
            send(command, (String) temp + DATA_SEPARATOR + (String) humidity);
            break;
        }
        case Bmp180: {
            if (bmpDriver->measurePressure()) {
                const double pressure = bmpDriver->getPressure();
                const double temp = bmpDriver->getTemperature();
                send(command, (String) pressure + DATA_SEPARATOR + (String) temp);
            } else {
                Serial.println(bmpDriver->getError());
            }
            break;
        }
    }
}


void send(Command command, String data) {
    // example 1: ^65&45$
    String response = RESPONSE_PREFIX + command + COMMAND_SUFFIX + data + RESPONSE_SUFFIX;
    Serial.println(response);
}


// commands
int readMq135(uint8_t pin) {
    return analogRead(pin);
}
