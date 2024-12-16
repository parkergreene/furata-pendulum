#include "stepper_utils.h"

float degsToSteps(float degrees, int stepsPerRevolution){
    return(float)(degrees * stepsPerRevolution / 360);
}