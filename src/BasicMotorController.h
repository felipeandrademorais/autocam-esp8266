#include <Arduino.h>
#include "MotorController.h"

class BasicMotorController : public MotorController {
private:
    const int LEFT_RIGHT_0 = D1;
    const int LEFT_RIGHT_1 = D2;
    const int UP_DOWN_0 = D3;
    const int UP_DOWN_1 = D4;

    void setAllToDown() {
        digitalWrite(LEFT_RIGHT_0, LOW);
        digitalWrite(LEFT_RIGHT_1, LOW);
        digitalWrite(UP_DOWN_0, LOW);
        digitalWrite(UP_DOWN_1, LOW);
    }

public:
    BasicMotorController() {
        pinMode(LEFT_RIGHT_0, OUTPUT);
        pinMode(LEFT_RIGHT_1, OUTPUT);
        pinMode(UP_DOWN_0, OUTPUT);
        pinMode(UP_DOWN_1, OUTPUT);
        setAllToDown();
    }

    void moveUp() override {
       Serial.println("Mover para cima");
        digitalWrite(UP_DOWN_0, LOW);
        digitalWrite(UP_DOWN_1, HIGH);
        delay(1000);
        setAllToDown();
    }

    void moveDown() override {
        Serial.println("Mover para baixo");
        digitalWrite(UP_DOWN_0, HIGH);
        digitalWrite(UP_DOWN_1, LOW);
        delay(1000);
        setAllToDown();
    }

    void moveLeft() override {
        Serial.println("Mover para esquerda");
        digitalWrite(LEFT_RIGHT_0, HIGH);
        digitalWrite(LEFT_RIGHT_1, LOW);
        delay(1000);
        setAllToDown();
    }

    void moveRight() override {
        Serial.println("Mover para direita");
        digitalWrite(LEFT_RIGHT_0, LOW);
        digitalWrite(LEFT_RIGHT_1, HIGH);
        delay(1000);
        setAllToDown();
    }
};
