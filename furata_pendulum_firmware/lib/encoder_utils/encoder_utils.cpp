#include "encoder_utils.h"

// Function to get the current encoder position in degrees
float getEncoderPosition(Encoder &enc, long encoderZero, int pulsePerRev){
  long currentPosition = enc.read() - encoderZero;

  float revs = (float)currentPosition / pulsePerRev;
  float degs = fmod(revs * 360.0 + 270, 360.0);

  if (degs < 0){
    degs +=360;
  }
  return degs;
}