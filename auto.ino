//knihovny
//https://github.com/adafruit/Adafruit-Motor-Shield-library
//https://github.com/Martinsos/arduino-lib-hc-sr04
//piny
const int trigPin = 9; 
const int trigPinR = 5;
//const int trigPinL = X;
const int echoPin = 10;
const int echoPinR = 2;
//const int echoPinL = Y;

//senzor
int vz;
int vzR;
int vzL;
long duration;
long durationR;
long durationL;
//const int minVZ = X;
//const int minVZS = Y;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  Serial.begin(115200);

}

void loop() {
  sensorsRead();// put your main code here, to run repeatedly:
  delay(1000);

}


void sensorsRead(){
  //front sensor
  //clears trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // vz = vzdálenost
  vz = duration * 0.034 / 2; //
  Serial.println(vz);
  //right sensor 
  
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  vzR = durationR * 0.034 / 2; //
 // Serial.println("senzor 2: ");
  Serial.println(vzR);
  //left sensor 
  /*
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  vzL = duration * 0.034 / 2; //
  */
}
