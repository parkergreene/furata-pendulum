#include <Arduino.h>
#include <AccelStepper.h>

// Define the pins for step and direction
#define STEP_PIN 2
#define DIR_PIN 5

// Steps per revolution (adjust this according to your motor)
const int stepsPerRevolution = 200; // For a typical 1.8° stepper motor (200 steps/rev)

// Create an instance of AccelStepper
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

// Delay between rotations in milliseconds
const int delayBetweenRotations = 2000;

// Target position for one full rotation
long targetPosition = stepsPerRevolution;

void setup() {
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(10000);    // Steps per second
  stepper.setAcceleration(10000); // Steps per second squared

  // Move the motor to the initial target position
  stepper.moveTo(targetPosition);
}

void loop() {
  // Move the motor to the target position
  if (stepper.distanceToGo() == 0) {
    // Wait for 3 seconds after completing one rotation
    delay(delayBetweenRotations);

    // Move another full rotation
    targetPosition += stepsPerRevolution;
    stepper.moveTo(targetPosition);
  }

  // Keep the stepper running
  stepper.run();
}
