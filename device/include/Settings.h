#ifndef SETTINGS_MODULE_H
#define SETTINGS_MODULE_H

// Definitions
#define SETTINGS_FILE_PATH "/settings.json"
#define SETTING_WIFI_SSID "wifiSsid"
#define SETTING_WIFI_PASSWORD "wifiPassword"

// App includes
#include "Core.h"

/**
 * @see setupSettings()
 */
void setupSettings();

/**
 * @see isSettingKeyValid()
 */
void getDeviceId(uid id);

/**
 * @see isSettingKeyValid()
 */
bool isSettingKeyValid(const char* key);

/**
 * @see setSetting()
 */
bool setSetting(const char* key, const char* value, bool save = true);

/**
 * @see getSetting()
 */
void getSetting(const char* key, char* value);

/**
 * @see saveSettings()
 */
bool saveSettings();

/**
 * @see getSetting()
 */
void loadSettings();

#endif
