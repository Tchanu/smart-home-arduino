#include <Arduino.h>
#include <drivers/DhtDriver.h>
#include <drivers/BmpDriver.h>
#include <drivers/MQ135Driver.h>
#include <CommandHandler.h>


const uint8_t MQ135_PIN = 0; // A0
const uint8_t DHT_PIN = 2; // D2

const auto commandHandler = new CommandHandler(new MQ135Driver(MQ135_PIN), new BmpDriver(), new DhtDriver(DHT_PIN));

void setup() {
    Serial.begin(9600);
    commandHandler->begin();
}

void loop() {
    if (Serial.available() > 0) {
        const auto command = (Command) Serial.read();
        commandHandler->handle(command);
    }
}
