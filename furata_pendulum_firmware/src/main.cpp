#include <Arduino.h>
#include <AccelStepper.h>

// Define the pins for step and direction
#define STEP_PIN 2
#define DIR_PIN 5

// Steps per revolution (adjust this according to your motor)
const int stepsPerRevolution = 200; // For a typical 1.8° stepper motor (200 steps/rev)

// Create an instance of AccelStepper
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

// Number of rotations
const int rotations = 10;

// Target position (steps for 10 rotations)
long targetPosition = rotations * stepsPerRevolution;

// Track whether the motor is moving forward or backward
bool movingForward = true;

void setup() {
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(1500);    // Steps per second
  stepper.setAcceleration(6000); // Steps per second squared

  // Start by moving forward
  stepper.moveTo(targetPosition);
}

void loop() {
  // Move the motor to the target position
  if (stepper.distanceToGo() == 0) {
    // When the current movement is complete, switch direction
    movingForward = !movingForward;
    targetPosition = movingForward ? rotations * stepsPerRevolution : -rotations * stepsPerRevolution;
    stepper.moveTo(targetPosition);
  }

  // Keep the stepper running
  stepper.run();
}