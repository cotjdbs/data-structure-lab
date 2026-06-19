#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class Car {
protected:
    int speed = 0;
    std::string name = "";
public:
    int gear = 0;

    Car() = default;

    Car(int s, const std::string& n, int g) : speed(s), name(n), gear(g) {}

    virtual ~Car() {}

    void changeGear(int g) {
        gear = g;
    }

    virtual void speedUp() {
        speed += 5;
    }

    void display() const {
        std::cout << "[" << name << "] : Gear=" << gear << " Speed" << speed << "kmph" << std::endl;
    }
};