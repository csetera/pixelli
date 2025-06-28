#pragma once

#include <cstddef>
#include <ArduinoJson.h>
#include <FastLED.h>

class SettingsManager {
public:
    /**
     * @brief Return the singleton instance of the logger.
     *
     * @return Logger&
     */
    static SettingsManager& get();

    // Disable copy semantics
    SettingsManager(const SettingsManager&) = delete;

    /**
     * @brief Get the Color for displaying the news
     *
     * @return CRGB
     */
    CRGB getNewsColor() {
        return newsColor;
    }

    uint8_t getDisplaySleepEnd() {
        // TODO configurable
        return 6;
    }

    uint8_t getDisplaySleepStart() {
        // TODO configurable
        return 18;
    }

    /**
     * @brief Get the Wifi SSID
     *
     * @return const char*
     */
    const char *getWifiSSID() {
        return wifiSSID;
    }

    /**
     * @brief Get the Wifi Password
     *
     * @return const char*
     */
    const char *getWifiPassword() {
        return wifiPassword;
    }

    /**
     * @brief Read all settings in from file system.
     *
     * @return true
     * @return false
     */
    bool readSettings();

    /**
     * @brief Clear all settings.
     */
    void reset();

    /**
     * @brief Send the settings JSON reponse.
     *
     * @param root
     */
    void sendSettingsResponse(JsonVariant &root);

    /**
     * @brief Set the Color for displaying the news
     *
     * @return CRGB
     */
    void setNewsColor(CRGB newColor) {
        newsColor = newColor;
    }

    /**
     * @brief Set the Wifi SSID
     *
     * @param value
     */
    void setWifiSSID(const char *value);

    /**
     * @brief Set the Wifi password
     *
     * @param value
     */
    void setWifiPassword(const char *value);

    /**
     * @brief Update the settings based on the specified JSON object.
     *
     * @param obj
     */
    void updateSettings(JsonObject &obj);

    /**
     * @brief Write out the current settings to the file system
     */
    void writeSettings();

private:
    static const size_t MAX_WIFI_SSID_LENGTH = 33;
    static const size_t MAX_WIFI_PASS_LENGTH = 65;

    static constexpr const char *NEWS_SETTINGS      = "News";
    static constexpr const char *NEWS_COLOR         = "Color";

    static constexpr const char *WIFI_SETTINGS      = "WiFi";
    static constexpr const char *WIFI_SSID_KEY      = "ssid";
    static constexpr const char *WIFI_PASS_KEY      = "pass";

    static constexpr const char *SETTINGS_FILE = "/settings.json";

    SettingsManager();

    CRGB newsColor;

    char *wifiSSID;
    char *wifiPassword;

    /**
     * @brief Update the news settings based on the JsonArray
     * information.
     *
     * @param settings
     */
    bool updateNewsSettings(JsonArray &settings);

    /**
     * @brief Update the wifi settings based on the JsonArray
     * information.
     *
     * @param settings
     */
    bool updateWifiSettings(JsonArray &settings);
};
