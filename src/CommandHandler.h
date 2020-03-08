//
// Created by tchan on 08-Mar-20.
//

#ifndef ATMEGA2560_COMMANDHANDLER_H
#define ATMEGA2560_COMMANDHANDLER_H

#include <drivers/MQ135Driver.h>
#include <drivers/BmpDriver.h>
#include <drivers/DhtDriver.h>

enum Command {
    MQ135 = 'A',
    Dht = 'B',
    Bmp180 = 'C',
};

class CommandHandler {
    MQ135Driver mq135Driver;
    BmpDriver bmpDriver;
    DhtDriver dhtDriver;
public:
    CommandHandler(MQ135Driver *mq135Driver, BmpDriver *bmpDriver, DhtDriver *dhtDriver) : mq135Driver(*
                                                                                                               mq135Driver),
                                                                                           bmpDriver(
                                                                                                   *bmpDriver),
                                                                                           dhtDriver(
                                                                                                   *dhtDriver) {}

    void handle(Command command);

    void begin();

private:
    void send(Command command, String data);
};


#endif //ATMEGA2560_COMMANDHANDLER_H
