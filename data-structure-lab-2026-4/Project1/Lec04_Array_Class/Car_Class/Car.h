#pragma once
#include "Car2.h"

class SportsCar : public Car {
public:
    bool bTurbo = false;

    SportsCar() : Car(0, "SportsCar", 1) {
    }

    void setTurbo(bool turboState = true) {
        this->bTurbo = turboState;
    }

    void speedUp() override {
        if (bTurbo) {
            speed += 20;
        }
        else {
            Car::speedUp();
        }
    }
};