#include <Arduino.h>
#include "WiFiManager.h"
#include "WebServerManager.h"
#include "MotorController.h"
#include "MQTTHandler.h"
#include "BasicMotorController.h"

WiFiManager wifiManager;
WebServerManager webServerManager;
BasicMotorController motorController;
MQTTHandler mqttHandler(&motorController);

void setup() {
    Serial.begin(115200);
    wifiManager.connect("frmilia", "rf222705");

    if (WiFi.status() == WL_CONNECTED) {
        mqttHandler.setCallback();
        mqttHandler.connect();
    } 
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        webServerManager.handleClient();
    } else {
        mqttHandler.handleClient();
    }
}
