#ifndef ENCODER_UTILS_H
#define ENCODER_UTILS_H

#include <Arduino.h>
#include <Encoder.h>

// Function prototype declaration
float getEncoderPosition(Encoder &enc, long encoderZero, int pulsePerRev);

#endif // ENCODER_UTILS_H
