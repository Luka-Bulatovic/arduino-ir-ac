// SerialCommunication.cpp
#include "SerialCommunication.h"

void SerialCommunication::sendMessage(const char* tag, const char* message) {
  stream->print(startMessageMarker);
  stream->print(tag);
  stream->print(SerialCommunication::separator);
  stream->print(message);
  stream->println(endMessageMarker);
}

void SerialCommunication::handleMessage() {
  if (stream->available() > 0) {
    this->receiveIncomingData();

    if (this->newDataAvailable) {
      handleMessage(this->incomingDataBuffer);

      this->newDataAvailable = false;
    }
  }
}

void SerialCommunication::registerHandler(const char* messageType, MessageHandler handler) {
  // handlers[messageType] = handler;
  handlers.insert(messageType, handler);
}

void SerialCommunication::handleMessage(char* message) {
  char* separatorPointer = strchr(message, SerialCommunication::separator);

  if (separatorPointer) {
    *separatorPointer = '\0';  // Split the message into two null-terminated strings.
    char* messageType = message;
    char* messageContent = separatorPointer + 1;

    if (handlers.containsKey(messageType)) {
      handlers[messageType](messageContent);
    }
    // if (handlers.find(messageType) != handlers.end()) {
    //   handlers[messageType](messageContent);
    // }
  }
}

void SerialCommunication::receiveIncomingData() {
  static boolean recvInProgress = false;
  static int ndx = 0;
  char startMarker = startMessageMarker;
  char endMarker = endMessageMarker;
  char rc;

  while (stream->available() > 0 && newDataAvailable == false) {
    rc = stream->read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        incomingDataBuffer[ndx] = rc;
        ndx++;
        if (ndx >= bufferSize) {
          ndx = bufferSize - 1;
        }
      } else {
        incomingDataBuffer[ndx] = '\0';  // terminate the string
        recvInProgress = false;
        ndx = 0;
        newDataAvailable = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
