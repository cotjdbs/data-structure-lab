#pragma once
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0);

    double getReal() const { return real; }
    double getImaginary() const { return imag; }

    void display() const;

    Complex operator+(const Complex& other) const;
};