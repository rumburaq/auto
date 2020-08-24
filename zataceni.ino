// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(110);
 
  motor.run(RELEASE);
}

void loop() {
  
  Serial.print("L"); // prvni fungue j e 2. ne""???????
  motor.setSpeed(100);
  motor.run(FORWARD);
  delay(500);
  motor.run(RELEASE);
  delay(1000);
  Serial.print("Prava");
  motor.setSpeed(100);
  motor.run(BACKWARD);
  delay(500);
  motor.run(RELEASE);
  delay(1000);
  Serial.print("cekani");
  //motor.run(RELEASE);
  delay(2000);
 
}
