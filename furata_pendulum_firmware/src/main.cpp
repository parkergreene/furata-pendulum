#include <Arduino.h>
#include <Encoder.h>
#include <AccelStepper.h>
#include "encoder_utils.h"
#include "stepper_utils.h"

// Encoder Setup
#define ENCODER_PIN_A 2 //define pins
#define ENCODER_PIN_B 3
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B); // Initialize the encoder object
int pulsePerRev = 2400;  // Encoder specifications
long encoderZero = 0;  // Variable to store the initial position as zero reference

// Stepper Setup
#define STEP_PIN 8
#define DIR_PIN 9
const int stepsPerRevolution = 200;
AccelStepper stepper(1,STEP_PIN, DIR_PIN);


void setup() {

  // Initialize serial communication
  Serial.begin(9600);
  //Serial.println("Rotary Encoder Test with 600 PPR (Pins 2 and 3)");
  // Set the current position as the zero reference
  encoderZero = encoder.read();

  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(10000);

}



float encoderPrev = getEncoderPosition(encoder, encoderZero, pulsePerRev);

void loop() {
  
  float encPosition = getEncoderPosition(encoder, encoderZero, pulsePerRev);
  
  float encChange = encPosition - encoderPrev;

  float move = degsToSteps(encChange, stepsPerRevolution);

  Serial.println(encChange, 2);

  stepper.move(move);
  stepper.run();

  encoderPrev = encPosition;
  //Serial.println(encPosition, 2);
  // Small delay for stability
  //delay(50);

}