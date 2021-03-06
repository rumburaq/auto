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
extern int vzZ; //(zadni) !!!
int minvz = 30; //(ne)bude se mněnit a muze se dat na #define
int minvzS = 30; //min. vzdálenost strana 30cm
int minvzZ = 30;
long duration; //cas za ktery letel zvuk od senzoru a zpet (stred) senzor
long durationR; //pravy senzor...
long durationL;
long durationZ;
unsigned long perv = 0; //pervious time 
unsigned long now = 0;
int interval = 100; //#define ?
  

void setup() {
  digitalWrite(RELE_PIN_1, LOW); // low = zapne se //
  digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0
  pinMode(RELE_PIN_1, OUTPUT); //                                  IN1    IN2  vysledek
  pinMode(RELE_PIN_2, OUTPUT);//                                    1      1   motor se otaci 1 smerem
  // je to tady protoze je to (asi) rychlejsi nez funkce //           1      0   motor stoji
  //digitalWrite(RELE_PIN_1, LOW); // low = zapne se //             0      1   motor stoji
  //digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0                     0      0   motor jede na 2 stranu

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

  delay(500);// aby se to nacetlo
}

void loop() {
  now = millis();
  if (now - perv > interval){ 
    perv = now;
    sensorsRead(); // nemuze tady bejt?
  }
  if ((vz < minvz) || (vzR < minvzS) || (vzL < minvzS)) { //pridat > 2 aby nekolildovalu s nulou

    if ((vz < minvz) && (vzR < minvzS) && (vzL < minvzS)) {
      pause();
      //otocka();
    }

    else if (vzR < vzL) {
      left();
    }

    else if (vzR > vzL) {
      right();
    }

    else {
      go();
    }
  }
  else {
    go();
  }

}
void sensorsRead() { 
  // mereni 30-40 tisicin sekundy
  //front sensor
  
  //"vycisti" trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // pulseIn zmeri cas v mikrosedundach jak dlouho zvukova vlna letela |//!? MOZNA PREJMENOVAT DURATION NA TIME
  vz = duration * 0.034 / 2; // vz = vzdálenost | s = t * v | s = duration * 0.043cm/micros |
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
  //delay(100);// 10 mereni  (za sekundu) ZRUSIT
  
  

  //back sensor

  /*digitalWrite(trigPinZ, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinZ, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinZ, LOW);
    durationZ = pulseIn(echoPinZ, HIGH);
    vzZ = durationZ * 0.034 / 2; //
    Serial.println("senzor Zadni____: ");
    Serial.println(vzZ);*/
}

void backSensor() {
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
  // delay(100); // 10 mereni /s (za sekundu)

}

void go() {
  digitalWrite(RELE_PIN_1, HIGH);
  digitalWrite(RELE_PIN_2, HIGH); //} 1 1
}

void pause() {
  digitalWrite(RELE_PIN_1, LOW);
  digitalWrite(RELE_PIN_2, HIGH); //} 0 1
}

void left() {
  motor.setSpeed(120); //nemelo by se tady nechat
  motor.run(BACKWARD);
}

void right() {
  motor.run(FORWARD);
}

void backward() {
  digitalWrite(RELE_PIN_1, LOW);
  digitalWrite(RELE_PIN_2, LOW); //} 0 0
}

void otocka() {
  int leftcount = 0;
  pause();
  //delay(2000) //!!??? je horni hranice aby nerozhodila senzory?
  while (vzZ > minvzZ) { //!! NEKDE POUZIT BACKSENSOR !!
    if (vzZ > minvzZ && leftcount == 0 ) {
      left();
      //delay(50) ?
      backward();
      leftcount = 1;
    }
    else if (vzZ > minvzZ && leftcount == 1) { //vyresit lag senzoru otestovat funkci na zpatecku (v hlave)
      //backward();
      motor.run(RELEASE);
    }
    else if (vzZ > minvz && leftcount == 1) {
      pause();
      fullright(); // musim vytvorit na z leva do prava a obracene
      go();
    }

  }

}

void fullright() {
  motor.run(FORWARD);
  delay(50); //mozna vic mozna min
  motor.run(RELEASE);
}

void fullleft() {
  motor.run(BACKWARD);
  delay(50); //mozna vic mozna min
  motor.run(RELEASE);
}
