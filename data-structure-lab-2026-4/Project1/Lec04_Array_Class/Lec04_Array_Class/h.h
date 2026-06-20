#pragma once
#include <iostream>

#define HEIGHT 8
#define WIDTH 8

extern int image[HEIGHT][WIDTH];

int findMaxBrightness(int img[HEIGHT][WIDTH], int height, int width);
