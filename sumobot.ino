#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>

const int LEFT = 0;
const int RIGHT = 1;
//const int FRONT = 2;
//const int BACK = 3;
const int SIDES = 2;
int ir_sensors[SIDES];

Adafruit_MotorShield AFMS;
Adafruit_DCMotor *left;
Adafruit_DCMotor *right;

void move_forward(int speed, int duration_ms) {
  right->setSpeed(speed);
  left->setSpeed(speed);
  right->run(FORWARD);
  left->run(FORWARD);
  delay(duration_ms);
}

void move_backward(int speed, int duration_ms) {
  right->setSpeed(speed);
  left->setSpeed(speed);
  right->run(BACKWARD);
  left->run(BACKWARD);
  delay(duration_ms);
}

void turn_left(int speed, int duration_ms) {
  // Slow inside the wheel, fast outside the wheel
  left->setSpeed(speed);
  right->setSpeed(speed * 2);
  left->run(FORWARD);
  right->run(FORWARD);
  delay(duration_ms);
}

void turn_right(int speed, int duration_ms) {
  // Fast inside the wheel, slow outside the wheel
  left->setSpeed(speed * 2);
  right->setSpeed(speed);
  left->run(FORWARD);
  right->run(FORWARD);
  delay(duration_ms);
}

void stop_moving() {
  right->setSpeed(0);
  left->setSpeed(0);
}

bool see_white(int direction) {
  return digitalRead(ir_sensors[direction]) == 0;
}

void setup() {
  Serial.begin(9600);

  AFMS = Adafruit_MotorShield();
  AFMS.begin();
  left = AFMS.getMotor(2);
  right = AFMS.getMotor(3);

  // for example...
  ir_sensors[LEFT] = 9;
  ir_sensors[RIGHT] = 10;
  //ir_sensors[FRONT] = 11;
  //ir_sensors[BACK] = 12;
  for (int i = 0; i < SIDES; i++) {
    pinMode(ir_sensors[i], INPUT);
  }
}

// https://pundit.pratt.duke.edu/wiki/ECE_110/Equipment/QTI
long rcTime(int pin) {
  pinMode(pin, OUTPUT);    // Sets pin as OUTPUT
  digitalWrite(pin, HIGH); // Pin HIGH
  delay(1);                // Waits for 1 millisecond
  pinMode(pin, INPUT);     // Sets pin as INPUT
  digitalWrite(pin, LOW);  // Pin LOW
  long time = micros();    // Tracks starting time
  while(digitalRead(pin)); // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time;             // Return decay time
}

void loop() {
  /*
  int speed = 50;

  // Idea for avoiding the white boundary lines...
  //while (see_white(BACK)) {
  //  move_forward(speed, 1);
  //}
  //while (see_white(FRONT)) {
  //  move_backward(speed, 1);
  //}
  while (see_white(LEFT)) {
    Serial.println("left is white");
    //turn_right(speed, 1);
  }
  while (see_white(RIGHT)) {
    Serial.println("right is white");
    //turn_left(speed, 1);
  }
  */
  Serial.println(rcTime());
  /*
  Ideas for strategies:
  - spin in a circle quickly towards the opponent
  - randomly move about then charge at opponent when we see them
  - charge straight at the opponent the moment the match starts
  - bait the opponent into coming near a boundary then push them out?
  */
}
