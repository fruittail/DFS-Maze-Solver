#include <Servo.h>

Servo myServo; 
const int servoPin = 10; 

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600); 
}

void loop() {
  myServo.write(90); 
  Serial.println("90");
  delay(1000);
   
  myServo.write(0);
  Serial.println("0");  
  delay(1000);

  myServo.write(180); 
  Serial.println("180");
  delay(1000);
}   