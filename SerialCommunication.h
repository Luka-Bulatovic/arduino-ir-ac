// SerialCommunication.h
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <Arduino.h>
#include <Stream.h>
#include <ArxContainer.h>

class SerialCommunication {
  private:
    typedef void (*MessageHandler)(const char* message);
    const static byte bufferSize = 64;
    char incomingDataBuffer[bufferSize];

    Stream* stream;
    arx::map<String, MessageHandler> handlers;
    bool newDataAvailable = false;

  public:
    static const char separator = '#';

    SerialCommunication(Stream* stream)
      : stream(stream)
    {}

    void sendMessage(const char* tag, const char* message);
    void handleMessage();
    void registerHandler(const char* messageType, MessageHandler handler);
    void receiveIncomingData();

  private:
    void handleMessage(char* message);
};

#endif