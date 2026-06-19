#include <iostream>
#include "Car.h"

int main() {
    Car normalCar(50, "NormalCar", 3);

    SportsCar sportsCar;

    sportsCar.changeGear(2);

    sportsCar.setTurbo(true);

    sportsCar.speedUp();

    normalCar.display();

    sportsCar.display();

    std::cout << "Press any key to close this window..." << std::endl;
    std::cin.get();
    std::cin.get();

    return 0;
}