#include <Encoder.h>

// Define encoder pins
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3

// Initialize the encoder object
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

// Encoder specifications
#define PULSES_PER_REVOLUTION 2400



// Variable to store the initial position as zero reference
long encoderZero = 0;

// Function to get the current encoder position in degrees
float getEncoderPosition(Encoder &enc, long encoderZero){
  long currentPosition = enc.read() - encoderZero;

  float revs = (float)currentPosition / PULSES_PER_REVOLUTION;
  float degs = fmod(revs * 360.0, 360.0);

  if (degs < 0){
    degs +=360;
  }
  return degs;
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Rotary Encoder Test with 600 PPR (Pins 2 and 3)");

  // Set the current position as the zero reference
  encoderZero = encoder.read();
}

void loop() {
  
  float position = getEncoderPosition(encoder, encoderZero);

  

  // Print the position and calculated values
  //Serial.print("Position: ");
  //Serial.print(currentPosition);
  //Serial.print(" | Degrees: ");
  Serial.println(position, 1);

  // Small delay for stability
  delay(50);
}
