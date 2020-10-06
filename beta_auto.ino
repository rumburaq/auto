//ta mrdka moc nefunguje ani to nejde zkompilovat nakej error /302 in program ?? ale uz asi vim jak na to a 
//spravim to hned zejtra lol 

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
int minvz = 30; //(ne)bude se mněnit a muze se dat na #define
int minvzS = 30; //min. vzdálenost strana 30cm
long duration; //cas za ktery letel zvuk od senzoru a zpet (stred) senzor
long durationR; //pravy senzor...
long durationL;
long durationZ;

void setup() {
  pinMode(RELE_PIN_1, OUTPUT); //                                  IN1    IN2  vysledek               
  pinMode(RELE_PIN_2, OUTPUT);//                                    1      1   motor se otaci 1 smerem
// je to tady protoze je to (asi) rychlejsi nez funkce //           1      0   motor stoji
  digitalWrite(RELE_PIN_1, LOW); // low = zapne se //               0      1   motor stoji
  digitalWrite(RELE_PIN_2, HIGH); //  } = 1 0                       0      0   motor jede na 2 stranu

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
  sensorsRead(); //nacti hodnoty ze senzorů
  if (vz < minvz) || (vzR < minvzS) || (vzL < minvzS) {
  
  if (vz < minvz) && (vzR < minvzS) && (vzL < minvzS) { //pokud jsi blízko prekazce zastav
    pause();
    //otocka();
  }

  else if (vzR < vzL){ //kdyz je na levo víc místa jed do leva
    left();
  }

  else if (vzR > vzL){
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

void sensorsRead(){ // nesmi to bejt void OPRAVIT na argumenty funkce
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
  vz = duration * 0.034 / 2; // vz = vzdálenost | s = t * v | s = duration * 0.043cm/µs |
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

  delay(100); // 10 mereni /s (za sekundu) ! zmennit na pouzití munkce milis();

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

  void backSensor(){ // ne na void
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
  delay(100); // 10 mereni /s (za sekundu)
  
  }

  void go(){
  digitalWrite(RELE_PIN_1, HIGH);              
  digitalWrite(RELE_PIN_2, HIGH); //} 1 1
  }

  void pause(){
    digitalWrite(RELE_PIN_1, LOW);              
    digitalWrite(RELE_PIN_2, HIGH); //} 0 1
  }

  void left(){
    motor.setSpeed(120); //nemelo by se tady nechat
    motor.run(BACKWARD);
  }

  void right(){
    motor.run(FORWARD);
  }

  void backward(){
    digitalWrite(RELE_PIN_1, LOW);              
    digitalWrite(RELE_PIN_2, LOW); //} 0 0
  }

  void otocka() { // to je mrdka to radsi ani nikdo nectete ani to zatim nefunguje
    int leftcount = 0;
    pause();
    //delay(2000) //!!??? je horni hranice aby nerozhodila senzory?
    while (vzZ > minvzZ){ //!! NEKDE POUZIT BACKSENSOR !!
      if (vzZ > minvzZ && leftcount == 0 ){
        left();
        //delay(50) ?
        backward();
        leftcount = 1;
      }
      else if (vzZ > minvzZ && leftcount == 1){ //vyresit lag senzoru otestovat funkci na zpatecku (v hlave) nastenka napsat funkci fullright a naopak
        //backward();
        motor.run(RELEASE);
      }
      else if (vzZ > minVZ && leftcount == 1){
        pause();
        rightfull(); // musim vytvorit na z leva do prava a obracene 
        go();
      }
      
    }
    
  }

  void fullright() { //mozna k nicemu
    motor.run(FORWARD);
    delay(50); //mozna vic mozna min
    motor.run(RELEASE);
  }

  void fullleft() {
    motor.run(BACKWARD); 
    delay(50); //mozna vic mozna min
    motor.run(RELEASE);
  }
