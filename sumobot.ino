/*
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_VL53L0X.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>

// https://www.makerguides.com/vl53l0x-distance-sensor-with-arduino/
// wiring:
// orange -> VIN
// grey -> GND
// green -> SCL
// blue -> SDA

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *right = AFMS.getMotor(2);
Adafruit_DCMotor *left = AFMS.getMotor(3);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void forward() {
  right->run(FORWARD);
  left->run(FORWARD);
  right->setSpeed(100);
  left->setSpeed(100);
}

void backward() {
  right->run(BACKWARD);
  left->run(BACKWARD);
  right->setSpeed(50);
  left->setSpeed(50);
}

void stop_car() {
   right->setSpeed(0);
   left->setSpeed(0);
}

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  lox.begin();
  lox.setMeasurementTimingBudgetMicroSeconds(200000); // 200 ms
}

void loop(){
  //forward();
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  bool is_phase_failure = measure.RangeStatus == 4;

  if (!is_phase_failure) {
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println("Out of range!");
  }
}
*/

#include <Wire.h>
#include <VL53L0X.h>

// inaccurate sensing?

VL53L0X sensor;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();
}