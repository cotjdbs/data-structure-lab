#include <iostream>
#include <iomanip>
#include "Complex.h"

int main() {
    Complex A(2.0, 3.1);
    Complex B(5.4, 1.2);

    std::cout << "A = " << std::fixed << std::setprecision(1) << A.getReal() << " " << A.getImaginary() << std::endl;
    std::cout << "B = " << std::fixed << std::setprecision(1) << B.getReal() << " " << B.getImaginary() << std::endl;

    std::cout << std::setprecision(2);

    std::cout << "A = ";
    A.display();
    std::cout << std::endl;

    std::cout << "B = ";
    B.display();
    std::cout << std::endl;

    Complex sum = A + B;
    std::cout << "A + B = ";
    sum.display();
    std::cout << std::endl;

    std::cout << "Press any key to close this window...";
    std::cin.get();

    return 0;
}