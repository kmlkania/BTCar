#include <SoftwareSerial.h>
#define PP 9
#define PT 8
#define LP 11
#define LT 10

SoftwareSerial bluetooth(4,7); //RX, TX
int bt;
int natalka_mode;
int reverse_mode;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("program start");
  pinMode(PP, OUTPUT);
  pinMode(PT, OUTPUT);
  pinMode(LP, OUTPUT);
  pinMode(LT, OUTPUT);
  natalka_mode = 0;
  reverse_mode = 0;
  stop();

}

void loop() {
  if (bluetooth.available() > 0){
    bt = bluetooth.read();
    Serial.println(bt);

    switch(bt){
      case '1':
        przod();
        reverse_mode = 0;
        break;
      case '2':
        tyl();
        break;
      case '3':
        prawo();
        check_natalka_mode();
        break;
      case '4':
        lewo();
        check_natalka_mode();
        break;
      case '5':
        natalka_mode = (natalka_mode + 1)%2;
        break;
      case '7':
        obrot_prawo();
        break;
      case 'a':
        reverse_mode = (reverse_mode + 1)%2;
        break;
      default:
        stop();
        break;    
    }   
  }
}

void stop(){
  Serial.println("stop");
  set_engine(LOW, LOW, LOW, LOW);
}

void przod(){
  Serial.println("przod");
  set_engine(HIGH, LOW, HIGH, LOW);
}

void tyl(){
  Serial.println("tyl");
  set_engine(LOW, HIGH, LOW, HIGH);
}

void prawo(){
  Serial.println("prawo");
  if (reverse_mode == 0){
    prawo_przod();
  }
  else {
    prawo_tyl();
  }
}

void lewo(){
  Serial.println("przod");
  if (reverse_mode == 0){
    lewo_przod();
  }
  else {
    lewo_tyl();
  }
}

void obrot_prawo(){
  Serial.println("obrot_prawo");
  set_engine(LOW, HIGH, HIGH, LOW);
}

void check_natalka_mode(){
  if (natalka_mode == 1){
    delay(500);
    stop();
  }
}

void prawo_przod(){
  set_engine(LOW, LOW, HIGH, LOW);
}

void prawo_tyl(){
  set_engine(LOW, LOW, LOW, HIGH);
}

void lewo_przod(){
  set_engine(HIGH, LOW, LOW, LOW);
}

void lewo_tyl(){
  set_engine(LOW, HIGH, LOW, LOW);
}


void set_engine(int v_PP, int v_PT, int v_LP, int v_LT){
  digitalWrite(PP, v_PP);
  digitalWrite(PT, v_PT);
  digitalWrite(LP, v_LP);
  digitalWrite(LT, v_LT);
}

