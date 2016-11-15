/**
 * File: Drone.ino
 * Author: ACM Team 4
 * Purpose:
 *  Outlines drone motor control, using the Arduino Servo library.
 */

// Include the Arduino servo library.
#include "Servo.h"

// The pin the status LED is on. To use the onboard LED, set this to 13.
#define SLED_PIN 13

// The value to consider maximum throttle.
#define MAX_THROTTLE 110

// Create a global servo instance to govern our one motor.
Servo motor;

/**
 * Function: setSLED
 * Sets the brightness of the defined status LED.
 * Parameters:
 *  b (byte): The brightness of the LED, from 0 to 255.
 * Returns:
 *  None.
 */
void setSLED(byte b)
{
  analogWrite(SLED_PIN, b);
}

/**
 * Function: setupServos
 * Attaches our global servo objects to the correct pins.
 * Parameters:
 *  None
 * Returns:
 *  None
 */
void setupServos()
{
  motor.attach(9);
}

/**
 * Function: armESC
 * Arms the electronic speed control using the arming sequence specified
 * in the extended ESC documentation.
 * NOTE: THIS IS A SYNCRHONOUS OPERATION.
 * Parameters:
 *  None
 * Returns:
 *  None
 */
void armESC() {
  
  // Write a low throttle signal for 1 second.
  motor.write(0);
  delay(1000);
  
  // Set the onboard LED to "on" to signal that we've begun
  // sending the ESC a generic throttle curve.
  setSLED(255);
  
  // Send the ESC a triangle wave.
  for( int i = 0; i < MAX_THROTTLE; ++i ) // Rising edge.
  {
    // Send the current throttle level to the ESC.
    motor.write(i);
    // Wait a while so the curve doesn't have a tiny period.
    delay(5);
  }
  for( int i = MAX_THROTTLE; i > 0; --i ) // Falling edge
  {
    motor.write(i);
    delay(5);
  }

  // Wait a while bringing the throttle back to perfect zero.
  delay(1000);
  motor.write(0);
  // Turn off the onboard LED to state that we've finished the
  // throttle curve.
  setSLED(0);
}

/**
 * Function: setMotorSpeed
 * Sets the speed of the motor.
 * Parameters:
 *  s (byte): The speed to set the motor to, from 0 to MAX_THROTTLE.
 * Returns:
 *  None.
 */
void setMotorSpeed( byte s )
{
  motor.write(s);
}

/**
 * Function: setup
 * Called as a callback at the start of the sketch to initialize "things".
 * Parameters:
 *  None
 * Returns:
 *  None
 */
void setup() {
  // Set up the servo library.
  setupServos();
  // Arm the ESC.
  armESC();
}

/**
 * Function: loop
 * Called repeatedly as a callback during microprocessor operation.
 * Parameters:
 *  None.
 * Returns:
 *  None.
 */
void loop() {

  // Oscillate the speed of the motor.
  for(int i = 0; i < 120; ++i)
  {
    // Write the current speed to the ESC.
    setMotorSpeed(i);
    // Wait a while so it hertz less.
    delay(15);
  }
  for(int i = 120; i > 0; --i)
  {
    setMotorSpeed(i);
    delay(15);
  }
}

