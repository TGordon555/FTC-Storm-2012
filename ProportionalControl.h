#ifndef PROPORTIONAL_CONTROL_H
#define PROPORTIONAL_CONTROL_H

typedef struct {
    float kP;
    float minError;
    float minOutput,maxOutput;
} ProportionalSettings;

bool proportionalControl(tMotor which,ProportionalSettings settings,float setpoint) {
    float error = setpoint - nMotorEncoder[which];
    bool ret = false;
    if(abs(error) < abs(settings.minError)) {
        error = 0;
        ret = true;
    }
    float output = settings.kP*error;
    motor[which] = output > settings.maxOutput ? settings.maxOutput :
                   output < settings.minOutput ? settings.minOutput :
                                                 output;
    return ret;
}

#endif
