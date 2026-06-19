#include <iostream>
#include "p.h"

int main() {
    Polynomial a, b;

    std::cout << "Enter the first polynomial A:" << std::endl;
    a.read();
    std::cout << std::endl;

    std::cout << "Enter the second polynomial B:" << std::endl;
    b.read();
    std::cout << std::endl;

    Polynomial c = a.add(b);

    std::cout << "A = ";
    a.display();
    std::cout << std::endl;

    std::cout << "B = ";
    b.display();
    std::cout << std::endl;

    std::cout << "A + B = ";
    c.display();
    std::cout << std::endl;

    std::cout << "Press any key to close this window..." << std::endl;
    std::cin.get();
    std::cin.get();

    return 0;
}