//NICE funkcni ale je potreba dodelat/zprovoznit
#include <AFMotor.h>

#define RELE_PIN_1 6
#define RELE_PIN_2 9

AF_DCMotor motor(2);

//konstanty senzoru
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
int vzZ; //(zadni) !!!
int minvz = 8; //(ne)bude se mněnit a muze se dat na #define
int minvzS = 8; //min. vzdálenost strana 30cm
int minvzZ = 8;
long duration; //cas za ktery letel zvuk od senzoru a zpet (stred) senzor
long durationR; //pravy senzor...
long durationL;
long durationZ;

//hodiny
unsigned long now;
unsigned long perv = 0;
int state = 0;
int interval = 100; //100 ms

int i, j, k, l = 40; //hodnody k predani od senzoru

void setup() {
  digitalWrite(RELE_PIN_1, LOW); // low = zapne se //
  digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0
  pinMode(RELE_PIN_1, OUTPUT); //                                  IN1    IN2  vysledek
  pinMode(RELE_PIN_2, OUTPUT);//       


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinZ, OUTPUT);
  pinMode(echoPinZ, INPUT);
  Serial.begin(115200);

  motor.setSpeed(120);
  motor.run(RELEASE);
}

void loop() {
  now = millis();
  if (now - perv > interval){ //casovac na 100 ms
    perv = now;
    //i = frontSensor();
    //j = rightSensor();
    k = leftSensor();
    Serial.println("ubehlo 100 ms - merim!");//chtelo byto odsud skok na switch
  /*  Serial.println(i);
    Serial.println(j);
    Serial.println(k); */
    
  }
  else if (k < minvzS) { //mensi nez 8
    Serial.println("triggerd!");
   /* if ((i < minvz) && (j < minvzS) && (k < minvzS)) {
      //pause();
      //otocka();
     // Serial.println("pause()");
    } */

     if (j < k) { //POZOR NA TO!
      //left();
      Serial.println("left()");
    }

    else if (j > k) {
      //right();
      Serial.println("right()");
    }

    else { //nemyslim si ze je vubec potreba
      //go();
      Serial.println("go()");
    }
  }
  /*else {
   // go();
   Serial.println("go()");
  } */
}

int frontSensor() { 
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
  //Serial.println("stred 1: ");
  //Serial.println(vz);
  return vz;
}

int rightSensor() {
  //right sensor

  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  vzR = durationR * 0.034 / 2; //
  //Serial.println("pravej 2: ");
  //Serial.println(vzR);
  return vzR;
}

int leftSensor() {
  //left sensor

  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  vzL = durationL * 0.034 / 2; //
  //Serial.println("levej 3: ");
  //Serial.println(vzL);
  return vzL;
}

int backSensor() {
  //back sensor

  digitalWrite(trigPinZ, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinZ, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinZ, LOW);
  durationZ = pulseIn(echoPinZ, HIGH);
  vzZ = durationZ * 0.034 / 2; //
  //Serial.println("senzor Zadni____: ");
  //Serial.println(vzZ);
  return vzZ;
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
  motor.run(BACKWARD);
}

void right() {
  motor.run(FORWARD);
}

void backward() {
  digitalWrite(RELE_PIN_1, LOW);
  digitalWrite(RELE_PIN_2, LOW); //} 0 0
}
