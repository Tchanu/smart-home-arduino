#include <Arduino.h>

int read_mq135(uint8_t pin);
void handle_serial(int bytes);
enum Command {
    MQ135 = 65,
};
void send(Command command, String data);

const int MQ135_PIN = 0; // A0


void setup() {
    Serial.begin(9600);
}


void loop() {
    if (Serial.available() > 0) {
        handle_serial(Serial.read());
    }
}


void handle_serial(int byte) {
    const auto command = (Command)byte;

    switch (command) {
        case MQ135:
            int air_quality = read_mq135(MQ135_PIN);
            send(command, (String)air_quality);
            break;
    }

    // sensorValue = read_mq135(MQ135_PIN);
    // Serial.println(sensorValue, DEC); // prints the value read
}

const String RESPONSE_PREFIX = "^";
const String COMMAND_SUFFIX = "&";
const String RESPONSE_SUFFIX = "$";

void send(Command command, String data) {
    // example: ^65&45$
    String response = RESPONSE_PREFIX + command + COMMAND_SUFFIX + data + RESPONSE_SUFFIX;
    Serial.println(response);
}



// commands
int read_mq135(uint8_t pin) {
    return analogRead(pin);
}
