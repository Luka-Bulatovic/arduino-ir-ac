# arduino-ir-ac

Serial.println(freeMemory(), DEC) - check free memory on stack + heap
Dynamic allocation seems to be causing heap fragmentation, should try to avoid it by using stack as much as possible. Will try to implement Map with limited size