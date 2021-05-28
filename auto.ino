#include <AFMotor.h>

AF_DCMotor motor2(2);
AF_DCMotor motor3(3);

//piny senzoru
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
int minvz = 25; //(ne)bude se mněnit a muze se dat na #define
int minvzS = 25; //min. vzdálenost strana 30cm
int minvzZ = 25;
long duration; //cas za ktery letel zvuk od senzoru a zpet (stred) senzor
long durationR; //pravy senzor...
long durationL;
long durationZ;
unsigned long perv = 0; //pervious time 
unsigned long now = 0;
int interval = 500; //#define ?

void setup() {
  //sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinZ, OUTPUT);
  pinMode(echoPinZ, INPUT);
  
  Serial.begin(115200);

  //zapne motory
  motor2.setSpeed(140);
  motor3.setSpeed(170);
  
  motor2.run(RELEASE);
  motor3.run(RELEASE);

  delay(3000);// aby se to nacetlo
  go();
 
}

void loop() {
  now = millis();
  if ((now - perv) > interval){ //ubehl interval
    perv = now;
    sensorsRead(); 
    if((vzZ < minvz) || (vzR < minvzS) || (vzL < minvzS)) { //prekrocil nejaky senz. min?
      if ((vzZ < minvz)) { //predni je moc blizko
        pause();
        delay(500);
        sensorsRead();
        if((vzL > vzR)){ //vic mista nalevo?
          left();
          delay(2000);
          pause();
        }
        else if((vzL < vzR)){
          right();
          delay(2000);
          pause();
        } 
      }
      else if((vzR < minvzS) || (vzL < minvzS)){ //levej nebo pravej je moc blizko
       pause(); 
       delay(500);
       sensorsRead();
        if((vzL > vzR)){
          left();
          delay(2000);
          pause();
        }
        else if((vzL < vzR)){
          right();
          delay(2000);
          pause();
        }
      } 
      else{
        go();
      }
    } 
    else{
      go(); 
    }
  }
}

void go(){
  motor2.run(FORWARD);
  motor3.run(FORWARD);
}

void pause(){ 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void right(){
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
}

void left(){
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
}

void backward(){
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
}

void sensorsRead() { 
  // mereni 30-40 tisicin sekundy
  //predni sensor
  
  //"vycisti" trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //pulseIn zmeri cas v mikrosedundach jak dlouho zvukova vlna letela 
  vz = duration * 0.034 / 2; // vz = vzdálenost | s = t * v | s = duration * 0.043cm/milis |
  Serial.println("stred 1: ");
  Serial.println(vz);
  //pravy sensor

  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  vzR = durationR * 0.034 / 2; //
  Serial.println("pravej 2: ");
  Serial.println(vzR);
  //levy sensor

  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  vzL = durationL * 0.034 / 2; //
  Serial.println("levej 3: ");
  Serial.println(vzL);
  delay(100);// 10 mereni  (za sekundu) ZRUSIT
  
  //zadni sensor

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
