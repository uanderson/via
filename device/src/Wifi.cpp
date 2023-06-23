// Lib includes
#include <Arduino.h>
#include <ESP8266WiFi.h>

// Module includes
#include "Wifi.h"
#include "Settings.h"
#include "Utils.h"

/**
 * Setup all the things related to WiFi.
 */
void setupWifi() {
  WiFi.mode(WIFI_AP_STA);

  createAccessPoint();
  connectToWifi();
}

/**
 * Creates an access point with the default SID and IP address.
 *
 * @param none
 * @return none
 */
void createAccessPoint() {
  uid deviceId = {0};
  getDeviceId(deviceId);

  char accessPointName[11] = "Via-";
  strncat(accessPointName, deviceId, 6);

  WiFi.softAP(accessPointName);
  IPAddress ip(192, 168, 68, 1);
  IPAddress gateway(192, 168, 68, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(ip, gateway, subnet);
}

/**
 * Attempts to connect to the WIFI. It has an optional timeout parameter
 * which sets the maximum time (in milliseconds) that the function will 
 * attempt to connect before giving up.
 *
 * @param timeout The time (in milliseconds) to attempt to connect before giving up.
 * @return None
 */
void connectToWifi() {
  char* wifiSsid = {0};
  char* wifiPassword = {0};

  getSetting(SETTING_WIFI_SSID, wifiSsid);
  getSetting(SETTING_WIFI_PASSWORD, wifiPassword);

  if (strlen(wifiSsid) == 0) {
    return;
  }

  WiFi.begin(wifiSsid, wifiPassword);
}
