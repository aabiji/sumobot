#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>

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

// NOTE: This must correspond to the pins we attached the OUT wires to on the arduino
int qti_sensor1 = 4;
int qti_sensor2 = 6;

int blue_sensor1 = 7;
int blue_sensor2 = 5;

void setup() {
  Serial.begin(9600);

  pinMode(blue_sensor1, INPUT);
  pinMode(blue_sensor2, INPUT);

  AFMS = Adafruit_MotorShield();
  AFMS.begin();
  left = AFMS.getMotor(2);
  right = AFMS.getMotor(3);
}

// https://pundit.pratt.duke.edu/wiki/ECE_110/Equipment/QTI
// B -> GND, W -> 5v, R -> pin 
bool qti_is_white(int pin) {
  pinMode(pin, OUTPUT);    // Sets pin as OUTPUT
  digitalWrite(pin, HIGH); // Pin HIGH
  delay(1);                // Waits for 1 millisecond
  pinMode(pin, INPUT);     // Sets pin as INPUT
  digitalWrite(pin, LOW);  // Pin LOW
  long time = micros();    // Tracks starting time
  while(digitalRead(pin)); // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time <= 100;
}

void debug_sensors() {
  if (qti_is_white(qti_sensor1) == LOW) {
    Serial.print("QTI1 sees white ");
  } else {
    Serial.print("QTI1 sees black ");
  }

  if (qti_is_white(qti_sensor2) == LOW) {
    Serial.print(" | QTI2 sees white ");
  } else {
    Serial.print("| QTI2 sees black ");
  }

  if (digitalRead(blue_sensor1) == LOW) {
    Serial.print(" | Blue1 sensor detected ");
  } else {
    Serial.print(" | Blue1 undetected ");
  }

  if (digitalRead(blue_sensor2) == LOW) {
    Serial.print(" | Blue2 sensor detected\n");
  } else {
    Serial.print(" | Blue2 sensor undetected\n");
  }
}

void loop() {
  debug_sensors();
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
  /*
  Ideas for strategies:
  - spin in a circle quickly towards the opponent
  - randomly move about then charge at opponent when we see them
  - charge straight at the opponent the moment the match starts
  - bait the opponent into coming near a boundary then push them out?
  */
}
