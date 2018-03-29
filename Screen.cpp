#include "Screen.h"

Screen::Screen(int width, int height, double fov): width(width), height(height), fov(fov){}

double Screen::getAspectRatio() {
    return width / double(height);
}
