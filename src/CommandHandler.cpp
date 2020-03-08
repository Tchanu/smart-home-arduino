#include "CommandHandler.h"
#include <drivers/MQ135Driver.h>

const String RESPONSE_PREFIX = "^";
const String COMMAND_SUFFIX = "&";
const String DATA_SEPARATOR = "|";
const String RESPONSE_SUFFIX = "$";

void CommandHandler::begin() {
    this->bmpDriver.begin();
    this->dhtDriver.begin();
}

void CommandHandler::handle(Command command) {
    switch (command) {
        case MQ135: {
            const int air_quality = this->mq135Driver.read();
            this->send(command, (String) air_quality);
            break;
        }
        case Dht: {
            const float temp = this->dhtDriver.readTemperature();
            const float humidity = this->dhtDriver.readHumidity();
            this->send(command, (String) temp + DATA_SEPARATOR + (String) humidity);
            break;
        }
        case Bmp180: {
            if (this->bmpDriver.measurePressure()) {
                const double pressure = this->bmpDriver.getPressure();
                const double temp = this->bmpDriver.getTemperature();
                send(command, (String) pressure + DATA_SEPARATOR + (String) temp);
            } else {
                // TODO: implement me
                Serial.println(this->bmpDriver.getError());
            }
            break;
        }
    }
}

void CommandHandler::send(Command command, String data) {
    // example 1: ^65&45$
    String response = RESPONSE_PREFIX + command + COMMAND_SUFFIX + data + RESPONSE_SUFFIX;
    Serial.println(response);
}
