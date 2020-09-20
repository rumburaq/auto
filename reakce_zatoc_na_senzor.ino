#include <AFMotor.h>
#define RELE_PIN_1 6
#define RELE_PIN_2 9

AF_DCMotor motor(2);

const int trigPin = 5; //modra // prostredni senzor
const int echoPin = 2;

const int trigPinL = 11;       // levej senzor
const int echoPinL = 13;

const int trigPinR = A4;       // pravej senzor
const int echoPinR = A5;

const int trigPinZ = A0;      // zadni senzor
const int echoPinZ = A3;

//senzor
int vz; //vzdalenost (stred)
int vzR;//vzdalenost prava...
int vzL;
int vzZ; //(zadni)
long duration; //cas za ktery letel zvuk od senzoru a zpet (stred) senzor
long durationR; //pravy senzor...
long durationL;
long durationZ;

void setup() {                                                  //   RELE STAVY
  pinMode(RELE_PIN_1, OUTPUT); //                                  IN1    IN2  vysledek               
  pinMode(RELE_PIN_2, OUTPUT);//                                    1      1   motor se otaci 1 smerem
// je to tady protoze je to (asi) rychlejsi nez funkce //           1      0   motor stoji
  digitalWrite(RELE_PIN_1, LOW); // low = zapne se //               0      1   motor stoji
  digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0                       0      0   motor jede na 2 stranu

             // set up Serial library at 9600 bps
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinZ, OUTPUT);
  pinMode(echoPinZ, INPUT);
  Serial.begin(115200);

  // turn on motor
  motor.setSpeed(120);
  motor.run(RELEASE);
}

void loop() {
  sensorsRead();
  /*
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
*/
  if(vzR <= 10) {
//   jed();
   Serial.println("jedu!");
   motor.run(BACKWARD);
  }

  else if(vzR > 10) {
    motor.run(RELEASE);
  }

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

void sensorsRead(){
  // mereni 30-40 tisicin sekundy
  //front sensor
  
  //clears trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // vz = vzdálenost
  vz = duration * 0.034 / 2; //
  Serial.println("stred 1: ");
  Serial.println(vz);
  //right sensor 
  
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  vzR = durationR * 0.034 / 2; //
  Serial.println("pravej 2: ");
  Serial.println(vzR);
  //left sensor 
  
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  vzL = durationL * 0.034 / 2; //
  Serial.println("levej 3: ");
  Serial.println(vzL);

  //back sensor 
  
  digitalWrite(trigPinZ, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinZ, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinZ, LOW);
  durationZ = pulseIn(echoPinZ, HIGH);
  vzZ = durationZ * 0.034 / 2; //
  Serial.println("senzor Zadni____: ");
  Serial.println(vzZ);
  
}
