#include <Preferences.h>

class StoreManager {
private:
    const char* preferencesNamespace = "wifi";

public:

    void saveCredentials(const String& ssid, const String& password) {
        Preferences preferences;
        preferences.begin(preferencesNamespace, false);
        preferences.putString("ssid", ssid);
        preferences.putString("password", password);
        preferences.end();
    }

    bool loadCredentials(String& ssid, String& password) {
        Preferences preferences;
        preferences.begin(preferencesNamespace, true);
        if (preferences.isKey("ssid") && preferences.isKey("password")) {
            ssid = preferences.getString("ssid");
            password = preferences.getString("password");
            preferences.end();
            return true;
        }
        preferences.end();
        return false;
    }
};
