#include <AFMotor.h>
#include <Servo.h>

//pin diff and constant values
AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);
int motorSpeed = 150;      
#define trigPin 8
#define echoPin 7
long duration;
#define irPin A0
int irThreshold = 330
;
Servo myservo;
int centerPos = 90;
int leftPos = 150;
int rightPos = 30;

//creating a node for direction
struct Node {
  char dir;
  Node* next;
};

Node* topNode = NULL;

void pushDirection(char d) {
  Node* newNode = new Node;
  newNode->dir = d;
  newNode->next = topNode;
  topNode = newNode;
}

void popDirection() {
  if (topNode != NULL) {
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
  }
}

void printDFS() {
  Serial.print("DFS STACK: ");
  printDFSRecursive(topNode);
  Serial.println();
}

void printDFSRecursive(Node* node) {
  if (node == NULL) return;
  printDFSRecursive(node->next);
  Serial.print(node->dir);
  Serial.print(" ");
}

//for loop avoiding
bool backtracking = false; 

//movements
void stopMotors() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void moveForward() {
  if (!backtracking) pushDirection('F');

  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
  delay(300);

  motorLeft.setSpeed(motorSpeed);
  motorRight.setSpeed(motorSpeed);
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);

  backtracking = false;
}

void turnLeft() {
  if (!backtracking) pushDirection('L');

  motorLeft.setSpeed(motorSpeed);
  motorRight.setSpeed(motorSpeed);
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(450);
  stopMotors();

  backtracking = false;
}

void turnRight() {
  if (!backtracking) pushDirection('R');

  motorLeft.setSpeed(motorSpeed);
  motorRight.setSpeed(motorSpeed);
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(450);
  stopMotors();

  backtracking = false;
}
//THIS THE PART THAT CAN BYPASS YOUR LOGIN PAGE AND ITS DANGERROUES
void uTurnBacktrack() {
  Serial.println("Dead end → Backtracking (POP)");
  popDirection();
  printDFS();

  backtracking = true;

  motorLeft.setSpeed(motorSpeed);
  motorRight.setSpeed(motorSpeed);
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(800); // 180-degree turn
  stopMotors();
}

//eyes for the path finding
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);

  myservo.attach(10);
  myservo.write(centerPos);

  stopMotors();
  delay(700);
}

void loop() {
//for goal detection
  int irValue = analogRead(irPin);
  Serial.print("IR: ");
  Serial.println(irValue);

  if (irValue < irThreshold) {
    stopMotors();
    Serial.println("=== GOAL REACHED! ===");
    Serial.print("Final IR Value: ");
    Serial.println(irValue);

    Serial.println("==== FINAL DFS PATH ====");
    printDFS();
    Serial.println("========================");
    while (1); // to stop the robot if ir is true
  }


  stopMotors();
  delay(100);

  myservo.write(centerPos);
  delay(300);
  int front = getDistance();
  Serial.print("Front: "); Serial.println(front);

  if (front > 20) {
    moveForward();
    printDFS();
    return;
  }

//if wall detected go backwards slight
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  delay(200);
  stopMotors();

  //sleft
  myservo.write(leftPos);
  delay(350);
  int left = getDistance();
  Serial.print("Left: "); Serial.println(left);

//sright
  myservo.write(rightPos);
  delay(350);
  int right = getDistance();
  Serial.print("Right: "); Serial.println(right);

  myservo.write(centerPos);

//decision making
  if (left > 20) {
    Serial.println("Turning LEFT");
    turnLeft();
  }
  else if (right > 20) {
    Serial.println("Turning RIGHT");
    turnRight();
  }
  else {
    Serial.println("All paths blocked → U-TURN BACKTRACK");
    uTurnBacktrack();
  }
//printing the dfs in stack
  printDFS();
}
