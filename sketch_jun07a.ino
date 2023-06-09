// Ultrasonic sensor pins
const int echoPinLeft = 5;
const int trigPinLeft = 6;
const int echoPinFront = 11;
const int trigPinFront = 12;
const int echoPinRight = 2;
const int trigPinRight = 4;

// Motor pins
int motorright = 9;
int motorrightdir = 7;
int motorleft = 10;
int motorleftdir = 8;

void setup() {
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(motorright, OUTPUT);
  pinMode(motorrightdir, OUTPUT);
  pinMode(motorleft, OUTPUT);
  pinMode(motorleftdir, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  int left = ultrasonic(echoPinLeft, trigPinLeft);
  int front = ultrasonic(echoPinFront, trigPinFront);
  int right = ultrasonic(echoPinRight, trigPinRight);

  Serial.print("[");
  Serial.print(left);
  Serial.print("cm, ");
  Serial.print(front);
  Serial.print("cm, ");
  Serial.print(right);
  Serial.println("cm]");

  delay(100); // Wait for 1/10th of a second.

  if (front <= 10 & left > 10 & right > 10) {
    // Obstacle in front, turn around
    leftTurn();
}
else if (front <= 10 & left <= 10 & right > 10) {
    // Obstacle on the left, turn right
    rightTurn();
}
else if (front >= 10 & right <= 10 & left > 10) {
    // Obstacle on the right, turn left
    forward();
}
else if (front <= 10 & right <= 10 & left > 10) {
    // Obstacle on the right, turn left
    leftTurn();
}
else if (front <= 10 & right <= 10 & left <= 10) {
    // Obstacle on the right, turn left
    around();
}
else {
    // No obstacle, move forward
    forward();
}
}

int ultrasonic(int echoPin, int trigPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void forward() {
  digitalWrite(motorrightdir, LOW);
  analogWrite(motorright, 50);
  digitalWrite(motorleftdir, LOW);
  analogWrite(motorleft, 50);
}

void stop() {
  analogWrite(motorright, 0);
  analogWrite(motorleft, 0);
}

void rightTurn() {
  digitalWrite(motorrightdir, HIGH);
  analogWrite(motorright, 50);
  digitalWrite(motorleftdir, LOW);
  analogWrite(motorleft, 50);
  delay(500); // Adjust the delay as per your requirement
  stop();
}

void leftTurn() {
  digitalWrite(motorrightdir, LOW);
  analogWrite(motorright, 50);
  digitalWrite(motorleftdir, HIGH);
  analogWrite(motorleft, 50);
  delay(500); // Adjust the delay as per your requirement
  stop();
}

void around() {
  digitalWrite(motorrightdir, HIGH);
  analogWrite(motorright, 50);
  digitalWrite(motorleftdir, HIGH);
  analogWrite(motorleft, 50);
  delay(1000); // Adjust the delay as per your requirement
  stop();
}
