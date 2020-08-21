//knihovny
//https://github.com/adafruit/Adafruit-Motor-Shield-library
//https://github.com/Martinsos/arduino-lib-hc-sr04
//piny
//const int trigPin = 5; //modra
//const int trigPinR = 5;
//const int trigPinL = 13;
//const int echoPin = 2;
//const int echoPinR = 2;
//const int echoPinL = 11;


const int trigPin = 5; //modra // prostredni senzor
const int echoPin = 2;

const int trigPinL = 11;       // levej senzor
const int echoPinL = 13;

const int trigPinR = A4;       // pravej senzor
const int echoPinR = A5;

const int trigPinZ = A0;
const int echoPinZ = A3;


//senzor
int vz;
int vzR;
int vzL;
int vzZ;
long duration;
long durationR;
long durationL;
long durationZ;
//const int minVZ = X;
//const int minVZS = Y;
//const int minZ = ;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinZ, OUTPUT);
  pinMode(echoPinZ, INPUT);
  Serial.begin(115200);

}

void loop() {
  sensorsRead();// put your main code here, to run repeatedly:
  //delay(1000);

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
  Serial.println("senzor 1: ");
  Serial.println(vz);
  //right sensor 
  
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  vzR = durationR * 0.034 / 2; //
  Serial.println("senzor 2: ");
  Serial.println(vzR);
  //left sensor 
  
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  vzL = durationL * 0.034 / 2; //
  Serial.println("senzor 3: ");
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
