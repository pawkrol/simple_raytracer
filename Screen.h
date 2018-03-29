#ifndef RIVAL_DEALER_SCREEN_H
#define RIVAL_DEALER_SCREEN_H


class Screen {

public:
    Screen(int width, int height, double fov);

    double getAspectRatio();

    int width;
    int height;

    double fov;

};


#endif //RIVAL_DEALER_SCREEN_H
