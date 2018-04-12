#ifndef RIVAL_DEALER_UTIL_H
#define RIVAL_DEALER_UTIL_H

class Util {

public:
    template <typename T>
    static T clamp(T lower, T upper, T value) {
        return value < lower? lower : (value > upper? upper: value);
    }

    template <typename T>
    static T max(T a, T b) {
        return a > b? a : b;
    }

    template <typename T>
    static T abs(T a) {
        return a < 0? -1 * a : a;
    }
};

#endif //RIVAL_DEALER_UTIL_H
