#include <ESP32Servo.h>

Servo leftServo;   // Left hand servo on pin 18
Servo rightServo;  // Right hand servo on pin 19

void setup() {
  Serial.begin(115200);
  
  // Allocate timer for PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  leftServo.attach(18);   // Attach left servo to GPIO 18
  rightServo.attach(19);  // Attach right servo to GPIO 19
  
  // Set initial position
  leftServo.write(90);
  rightServo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');
    
    if (commaIndex > 0) {
      int leftAngle = data.substring(0, commaIndex).toInt();
      int rightAngle = data.substring(commaIndex + 1).toInt();
      
      // Constrain angles to valid servo range
      leftAngle = constrain(leftAngle, 0, 180);
      rightAngle = constrain(rightAngle, 0, 180);
      
      leftServo.write(leftAngle);
      rightServo.write(rightAngle);
    }
  }
  delay(20);  // Small delay to stabilize
}