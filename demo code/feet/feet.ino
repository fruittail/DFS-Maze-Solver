#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
void setup() {
}

void loop() {
  // Forward
  motor1.run(FORWARD);motor2.run(FORWARD);
  // Accelerate from zero to maximum speed
    motor1.setSpeed(255);motor2.setSpeed(255);
    delay(1000);

  // Now turn off motor
  motor1.run(RELEASE); motor2.run(RELEASE);
  delay(500);


  // Backward
  motor1.run(BACKWARD);motor2.run(BACKWARD);
    motor1.setSpeed(255);motor2.setSpeed(255);
    delay(1000);

  // Now turn off motor
  motor1.run(RELEASE); motor2.run(RELEASE);
    delay(500);


  //Turn Left
   motor1.run(FORWARD);motor2.run(FORWARD);
    motor1.setSpeed(200);motor2.setSpeed(255);
    delay(1000);

  // Now turn off motor
  motor1.run(RELEASE); motor2.run(RELEASE);
    delay(500);

    //Turn Right
   motor1.run(FORWARD);motor2.run(FORWARD);
    motor1.setSpeed(255);motor2.setSpeed(200);
    delay(1000);

  // Now turn off motor
  motor1.run(RELEASE); motor2.run(RELEASE);
    delay(500);
}