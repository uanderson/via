// Lib includes
#include "Arduino.h"
#include "ArduinoJson.h"
#include "EEPROM.h"
#include "LittleFS.h"

// Module includes
#include "Settings.h"
#include "Utils.h"

uid cachedDeviceId = {0};
StaticJsonDocument<256> cachedSettings;

/**
 * Setups anything related to settings.
 */
void setupSettings() { loadSettings(); }

/**
 * Gets the device ID stored in EEPROM, or generates a new one if not found.
 * If a cached device id exists, returns it instead of querying EEPROM.
 *
 * @param deviceId for this specific device
 */
void getDeviceId(uid deviceId) {
  if (strcmp(cachedDeviceId, "") > 0) {
    strcpy(deviceId, cachedDeviceId);

    return;
  }

  char deviceIdIsSaved = 0;

  EEPROM.get(0, deviceIdIsSaved);
  EEPROM.get(1, cachedDeviceId);

  if (deviceIdIsSaved != 1) {
    generateId(cachedDeviceId);

    EEPROM.put(0, 1);
    EEPROM.put(1, cachedDeviceId);
    EEPROM.commit();
  }

  strcpy(deviceId, cachedDeviceId);
}

/**
 * Checks whether the passed settink key is valid or not.
 *
 * @param key to be verified
 */
bool isSettingKeyValid(const char* key) {
  return strcmp(key, SETTING_WIFI_SSID) == 0 ||
         strcmp(key, SETTING_WIFI_PASSWORD) == 0;
}

/**
 * Sets a setting by key and value.
 *
 * @param key to be set
 * @param value to be set
 * @param save whether the setting should be saved or not
 * @return true if the setting was saved successfully, false otherwise.
 */
bool setSetting(const char* key, const char* value, bool save) {
  if (isSettingKeyValid(key)) {
    cachedSettings[key] = value;

    if (save) {
      return saveSettings();
    }

    return false;
  }

  return false;
}

/**
 * Gets a setting by key.
 *
 * @param key to be queried
 * @param value to be filled
 * @return a char string value
 */
void getSetting(const char* key, char* value) {
  if (cachedSettings.containsKey(key)) {
    strcpy(value, cachedSettings[key]);
  }
}

/**
 * This function loads the device's settings from a JSON file stored in the
 * file system. If the file is not found or there is an error while
 * deserializing the file, default settings are used instead.
 */
void loadSettings() {
  if (!LittleFS.exists(SETTINGS_FILE_PATH)) {
    return;
  }

  auto settingsFile = LittleFS.open(SETTINGS_FILE_PATH, "r");

  if (!settingsFile) {
    return;
  }

  deserializeJson(cachedSettings, settingsFile);
  settingsFile.close();

  String jsonContent;
  serializeJson(cachedSettings, jsonContent);
}

/**
 * Saves the settings to the file system.
 *
 * @return true if the settings were saved successfully, false otherwise.
 */
bool saveSettings() {
  auto settingsFile = LittleFS.open(SETTINGS_FILE_PATH, "w");

  if (!settingsFile) {
    return false;
  }

  String jsonContent;
  serializeJson(cachedSettings, jsonContent);

  settingsFile.print(jsonContent);
  settingsFile.close();

  return true;
}