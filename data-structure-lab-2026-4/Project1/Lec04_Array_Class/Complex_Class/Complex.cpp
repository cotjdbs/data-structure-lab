#include "Complex.h"
#include <iomanip>

Complex::Complex(double r, double i) : real(r), imag(i) {}

void Complex::display() const {
    std::cout << std::fixed << std::setprecision(2);

    std::cout << real;
    if (imag >= 0) {
        std::cout << " + " << imag << "i";
    }
    else {
        std::cout << " - " << -imag << "i";
    }
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}