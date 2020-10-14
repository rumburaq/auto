//je to lepsi? tot otázka 

unsigned long now;
unsigned long perv = 0;
int state = 0;
int interval = 100; //100 ms

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  now = millis();
  if (now - perv > interval){ 
    perv = now;
    state = 1; //chtelo byto odsud skok na switch
  }
  if ((vz < minvz) || (vzR < minvzS) || (vzL < minvzS)) { //pridat > 2 aby nekolildovalu s nulou?

    if ((vz < minvz) && (vzR < minvzS) && (vzL < minvzS)) {
      state = 2;
      //otocka();
    }

    else if (vzR < vzL) {
      state = 3;
    }

    else if (vzR > vzL) {
      state = 4
    }
  }
  else {
    state = 0;
  }
switch (state) {
    case 0:
    //neubehlo 100ms
    //go() ale nedelal bych to
      break;
    case 1:
    //ubehlo 100ms
    SensorsRead();
      break;
    case 2:
    pause();
      break;//??
    case 3:
      left();
      break;
    case 4:
      right();
      break;
  }
  
}
