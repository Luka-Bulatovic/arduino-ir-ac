// MideaACController.h

#ifndef MIDEAACCONTROLLER__H
#define MIDEAACCONTROLLER__H

#include <IRremote.h>

enum class AcMode {
    COOL = 0x0,
    HEAT = 0xC,
    AUTO = 0x8,
    HUMIDITY_EXTRACTION = 0xD
};

enum class FanSpeed {
    SPEED_1 = 0x9,
    SPEED_2 = 0x5,
    SPEED_3 = 0x3,
    AUTO = 0xB,
    OFF = 0xE
};

class MideaACController {
public:
    IRsend irsend;

    MideaACController() : irsend(IRsend(3)) {  }

    void executeCommand(AcMode mode, int temp, FanSpeed fanSpeed) {
        byte commandByte = static_cast<byte>(fanSpeed) << 4 | 0xF;
        int tempCode = getTemperatureCode(temp);

        if (tempCode < 0) {
            Serial.print(F("Failed to convert temperature: "));
        } else {
            sendCommand(commandByte, ((byte) tempCode) << 4 | static_cast<byte>(mode));
        }
    }

    void stop() {
        sendCommand(0x7B, 0xE0);
    }

private:
    int getTemperatureCode(int temp) {
        if ((temp < 17) || (temp > 30)) {
            return -1;
        }

        static const int tempCodes[] = {0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 9, 8, 10, 11};
        return tempCodes[temp - 17];
    }

    void sendCommand(byte b1, byte b2) {
        emitStartSignal();
        emitByte(0xB2);
        emitByte(b1);
        emitByte(b2);
        emitEndSignal();

        // Repeating the command for reliability
        emitStartSignal();
        emitByte(0xB2);
        emitByte(b1);
        emitByte(b2);
        emitEndSignal();
    }

    void emitStartSignal() {
        irsend.enableIROut(38);
        irsend.mark(4200);
        irsend.space(4500);
    }

    void emitEndSignal() {
        irsend.mark(550);
        irsend.space(4500);
    }

    void emitByte(byte b) {
        byte cur = b;
        byte mask = 0x80;

        for (int i = 0; i < 8; i++) {
            emitBit(cur & mask);
            mask >>= 1;
        }

        cur = ~b;
        mask = 0x80;

        for (int i = 0; i < 8; i++) {
            emitBit(cur & mask);
            mask >>= 1;
        }
    }

    void emitBit(bool isOne) {
        irsend.mark(450);
        if (isOne) {
            irsend.space(1700);
        } else {
            irsend.space(600);
        }
    }
};

#endif