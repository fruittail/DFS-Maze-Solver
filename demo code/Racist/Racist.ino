const int irPin = A0;  
int sensorValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(irPin);  
  Serial.println(sensorValue);      
  delay(100);
}   