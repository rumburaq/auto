#include <AFMotor.h>
#define RELE_PIN_1 6
#define RELE_PIN_2 9

AF_DCMotor motor(2);

void setup() {                                                  //   RELE STAVY
  pinMode(RELE_PIN_1, OUTPUT); //                                  IN1    IN2  vysledek               
  pinMode(RELE_PIN_2, OUTPUT);//                                    1      1   motor se otaci 1 smerem
// je to tady protoze je to (asi) rychlejsi nez funkce //           1      0   motor stoji
  digitalWrite(RELE_PIN_1, LOW); // low = zapne se //               0      1   motor stoji
  digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0                       0      0   motor jede na 2 stranu

  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(120);
  motor.run(RELEASE);
}

void loop() {
  
  Serial.print("L"); // 130 na oba je nice 
  motor.setSpeed(135);
  motor.run(FORWARD);
  delay(150);
  motor.run(RELEASE);
  delay(1000);
  Serial.print("Prava");
  motor.setSpeed(135);
  motor.run(BACKWARD);
  delay(150);
  motor.run(RELEASE);
  delay(1000);
  Serial.print("cekani");
  //motor.run(RELEASE);
  delay(2000);

}

void stuj() {
  digitalWrite(RELE_PIN_1, LOW);
  digitalWrite(RELE_PIN_2, HIGH); // } 0 1
  
}

void backwards() {
  digitalWrite(RELE_PIN_1, LOW);
  digitalWrite(RELE_PIN_2, LOW); // } 1 1
  
}

void  jed() {
  digitalWrite(RELE_PIN_1, HIGH);
  digitalWrite(RELE_PIN_2, HIGH); // } 0 0
}
