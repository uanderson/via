#include "Arduino.h"
#include "EEPROM.h"
#include "LittleFS.h"

// App includes
#include "Core.h"
#include "Settings.h"
#include "Utils.h"
#include "Wifi.h"

#define LOOP_DELAY 10

/**
 * Starts all the services needed for the device to operate
 */
void setup() {
  Serial.begin(115200);
  EEPROM.begin(22);
  LittleFS.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  setupWifi();
  setupSettings();
}

/*
 * Handles loopy things.
 */
void loop() {
  static unsigned long lastChangeTime = 0;
  static bool ledState = false;

  if (millis() - lastChangeTime >= 1000) {
    lastChangeTime = millis();
    ledState = !ledState;

    digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
  }
}
