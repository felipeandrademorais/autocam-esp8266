#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>
#include <ESP8266WiFi.h> 
#include "MotorController.h"

class MQTTHandler {
private:
    WiFiClient espClient;
    PubSubClient client;
    MotorController* motorController;
    String clientID;

public:

    MQTTHandler(MotorController* controller) : motorController(controller), client(espClient) {
        client.setServer("broker.hivemq.com", 1883);
        clientID = "ESP8266Client-" + String(ESP.getChipId());
    }

    void setCallback() {
        client.setCallback([this](char* topic, byte* payload, unsigned int length) {
            this->handleMessage(topic, payload, length);
        });
    }

    void handleMessage(char* topic, byte* payload, unsigned int length) {
        String message = "";
        for (unsigned int i = 0; i < length; i++) {
            message += (char)payload[i];
        }

        if (String(topic) == "motor/control") {
            if (message == "UP") motorController->moveUp();
            else if (message == "DOWN") motorController->moveDown();
            else if (message == "LEFT") motorController->moveLeft();
            else if (message == "RIGHT") motorController->moveRight();
        }
    }

    void connect() {
        while (!client.connected()) {
            Serial.println("Conectando ao MQTT...");
            if (client.connect(clientID.c_str())) {
                Serial.println("Conectado");
                client.subscribe("motor/control");
            } else {
                Serial.print("Falhou, rc=");
                Serial.print(client.state());
                Serial.println(" tentando novamente em 5 segundos");
                delay(5000);
            }
        }
    }

    void handleClient() {
        if (!client.loop()) {
            Serial.println("Falha ao conectar ao broker MQTT");
            delay(5000);
        }
    }
};

#endif