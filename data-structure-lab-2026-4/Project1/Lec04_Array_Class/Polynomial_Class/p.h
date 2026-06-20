#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>

#define MAX_DEGREE 80

class Polynomial {
private:
    int degree;
    float coef[MAX_DEGREE];

public:
    Polynomial() {
        degree = 0;
        for (int i = 0; i < MAX_DEGREE; i++) {
            coef[i] = 0.0f;
        }
    }

    void read() {
        std::cout << "Enter degree: ";
        std::cin >> degree;

        if (degree < 0 || degree >= MAX_DEGREE) {
            std::cout << "Error: Invalid degree. Setting degree to 0." << std::endl;
            degree = 0;
        }

        std::cout << "Enter coefficients (" << degree + 1 << "): ";
        for (int i = 0; i <= degree; i++) {
            std::cin >> coef[i];
        }
    }

    Polynomial add(const Polynomial& other) const {
        Polynomial result;
        result.degree = std::max(this->degree, other.degree);

        for (int i = 0; i <= result.degree; i++) {
            float c1 = (i <= this->degree) ? this->coef[i] : 0.0f;
            float c2 = (i <= other.degree) ? other.coef[i] : 0.0f;
            result.coef[i] = c1 + c2;
        }

        while (result.degree > 0 && result.coef[result.degree] == 0.0f) {
            result.degree--;
        }

        return result;
    }

    void display() const {
        std::cout << std::fixed << std::setprecision(1);

        bool first_term_printed = false;

        for (int i = degree; i >= 0; i--) {
            if (coef[i] == 0.0f && (degree != 0 || i != 0)) {
                continue;
            }

            if (first_term_printed) {
                std::cout << " + ";
            }

            std::cout << coef[i];

            if (i > 0) {
                std::cout << " x^" << i;
            }

            first_term_printed = true;
        }

        if (!first_term_printed) {
            std::cout << "0.0";
        }
    }
};