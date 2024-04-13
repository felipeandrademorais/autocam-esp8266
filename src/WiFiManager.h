#include <ESP8266WiFi.h>

class WiFiManager {
public:
    void connect(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);
        Serial.print("Tentando conectar");
        int retries = 0;
        while (WiFi.status() != WL_CONNECTED && retries < 20) {
            delay(500);
            Serial.print(".");
            retries++;
        }
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("Falha ao conectar, iniciando AP");
            WiFi.softAP("ESP_Config", "12345678");
        } else {
            Serial.println("Conectado ao WiFi");
        }
    }
};
