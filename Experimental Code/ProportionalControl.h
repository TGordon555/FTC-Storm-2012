#ifndef PROPORTIONAL_CONTROL_H
#define PROPORTIONAL_CONTROL_H

typedef struct {
    float kP;
    float maxError;
    float minOutput,maxOutput;
} ProportionalSettings;

void proportionalControl(tMotor which,ProportionalSettings settings,float setpoint) {
    float error = setpoint - nMotorEncoder[which];
    if(abs(error) < abs(settings.maxError)) {
        error = 0;
    }
    float output = settings.kP*error;
    motor[which] = output > settings.maxOutput ? settings.maxOutput :
                   output < settings.minOutput ? settings.minOutput :
                                                 output;
}

#endif
