#include "color.hpp"
#include <math.h>

unsigned char encode(float x){
    if(x < 0.0f) return static_cast<unsigned char>(0);
    else if(x > 1.0f) return static_cast<unsigned char>(255);
    else return static_cast<unsigned char>(255.0f * powf(x, 1.0f/2.2f));
}

float decode(unsigned char x){
    return powf(static_cast<float>(x) / 255.0f, 2.2f);
}