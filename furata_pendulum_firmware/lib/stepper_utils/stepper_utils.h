#ifndef STEPPER_UTILS_H
#define STEPPER_UTILS_H

#include <Arduino.h>
#include <AccelStepper.h>

// Function prototype declaration

float degsToSteps(float degrees, int stepsPerRevolution);

#endif // STEPPER_UTILS_H