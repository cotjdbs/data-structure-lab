#include "h.h"

int main() {
    int maxVal = findMaxBrightness(image, HEIGHT, WIDTH);

    std::cout << "Maximum pixel brightness of the image: " << maxVal << std::endl;

    std::cout << "Press any key to close this window...";
    std::cin.get();

    return 0;
}