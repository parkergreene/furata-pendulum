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

//PID setup
float kp = 1;
float ki = 0.005;
float kd = 0.000;
float bias = 0;
float setpoint = 90;

float error_prev = 0;
float integral = 0;
float derivative = 0;
float move_deg = 0;
float error = 0;

unsigned long timestamp = 0;
unsigned long timestamp_prev = 0;
int counter = 0;

const double enc_guard_min = 60;
const double enc_guard_max = 120;

void setup() {

  // Initialize serial communication
  Serial.begin(9600);
  //Serial.println("Rotary Encoder Test with 600 PPR (Pins 2 and 3)");
  // Set the current position as the zero reference
  encoderZero = encoder.read();

  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(10000);

}
//float encoderPrev = getEncoderPosition(encoder, encoderZero, pulsePerRev);

void loop() {
  
  stepper.move(move_deg);

  float encPosition = getEncoderPosition(encoder, encoderZero, pulsePerRev);
  timestamp = millis();
  counter++;
  //float encChange = encPosition - encoderPrev;

  //float move = degsToSteps(encChange, stepsPerRevolution);
  //stepper.move(move);
  //stepper.run();

  float interval = timestamp - timestamp_prev;
  timestamp_prev = timestamp; 


  error = setpoint - encPosition;
  integral = integral + (error * interval);
  derivative = (error - error_prev) / interval;
  move_deg = (kp * error) + (ki * integral) + (kd * derivative) + bias;

  error_prev = error;


  //Serial.println(encPosition, 2);
  Serial.println("Encoder Position:" + String(encPosition) + "| move_deg"+ String(move_deg));

  //if (encPosition < enc_guard_min || encPosition > enc_guard_max){
  //  break;
  //}


  //encoderPrev = encPosition;
  //Serial.println(encPosition, 2);
  // Small delay for stability
  //delay(50);

}