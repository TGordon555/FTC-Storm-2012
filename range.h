#ifndef RANGE_H
#define RANGE_H

float scaleValue(float minIn,float maxIn,
                 float minOut,float maxOut,
                 float value) {
    float rangeIn = maxIn-minIn;
    float rangeOut = maxOut-minOut;
    return (rangeOut/rangeIn)*(value-minIn)+minOut;
}

float scaleJoystickValue(float minOut,float maxOut,
                         float value) {
    return scaleValue(-128,127,minOut,maxOut,value);
}

float clamp(float value,float min,float max) {
    return value < min ? min :
           value > max ? max :
                         value;
}

#endif
