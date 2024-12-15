#include <Arduino.h>
#include <Encoder.h>
#include "encoder_utils.h"

// Encoder Setup
#define ENCODER_PIN_A 2 //define pins
#define ENCODER_PIN_B 3
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B); // Initialize the encoder object
int pulsePerRev = 2400;  // Encoder specifications
long encoderZero = 0;  // Variable to store the initial position as zero reference


void setup() {

  // Initialize serial communication
  Serial.begin(9600);
  //Serial.println("Rotary Encoder Test with 600 PPR (Pins 2 and 3)");
  // Set the current position as the zero reference
  encoderZero = encoder.read();
}

void loop() {

  float position = getEncoderPosition(encoder, encoderZero, pulsePerRev);
  // Print the position and calculated values
  //Serial.print("Position: ");
  //Serial.print(currentPosition);
  //Serial.print(" | Degrees: ");
  Serial.println(position, 2);
  // Small delay for stability
  delay(50);

}