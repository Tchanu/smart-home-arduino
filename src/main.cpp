#include <Arduino.h>
#include <DHT.h>

int readMq135(uint8_t pin);

void handle_serial(int bytes);

enum Command {
    MQ135 = 65,
    Dht = 66,
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

auto dhtDriver = new DhtDriver(DHT(DHT_PIN, DHT22));

void setup() {
    Serial.begin(9600);
    dhtDriver->begin();
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
            int air_quality = readMq135(MQ135_PIN);
            send(command, (String) air_quality);
            break;
        }
        case Dht: {
            float temp = dhtDriver->readTemperature();
            float humidity = dhtDriver->readHumidity();
            send(command, (String) temp + DATA_SEPARATOR + (String) humidity);
            break;
        }
    }
}


void send(Command command, String data) {
    // example: ^65&45$
    String response = RESPONSE_PREFIX + command + COMMAND_SUFFIX + data + RESPONSE_SUFFIX;
    Serial.println(response);
}


// commands
int readMq135(uint8_t pin) {
    return analogRead(pin);
}
