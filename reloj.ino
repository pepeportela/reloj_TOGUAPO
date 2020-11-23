// TODO: Crear una flag de activación de los movimientos de los servos. Si esta desactivada los servos no se mueven pero el programa sigue en ejecución. Ideal para las noches y mostrar mensajes.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <DS3231.h>

// Este es el PCA principal con default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41, Wire);
// esta será la direccion del PCA esclavo/puenteado  TODO: Soldar los pines del PCA
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define pos0  SERVOMIN*2
#define pos270  2*SERVOMIN/3 // this is the 'minimum' pulse length count (out of 4096)
#define pos90 2*SERVOMAX/3 // this is the 'maximum' pulse length count (out of 4096)

// Definicion de caracteres según esta levantado el segemento o bajado. Se escriben en este orden "gfdecba"
const char charEmpty[7] = "0000000";
const char char0[7] = "1110111";
const char char1[7] = "0100100";
const char char2[7] = "1011101";
const char char3[7] = "1101101";
const char char4[7] = "0101110";
const char char5[7] = "1101011";
const char char6[7] = "1111011";
const char char7[7] = "0100101";
const char char8[7] = "1111111";
const char char9[7] = "0101111";
const char chara[7] = "0111111";
const char charb[7] = "1111010";
const char charc[7] = "1010011";
const char chard[7] = "1111100";
const char chare[7] = "1011011";
const char charf[7] = "0011011";
const char charh[7] = "0111110";
const char charl[7] = "1010010";
const char charp[7] = "0011111";
const char charu[7] = "1110110";

// Barrido
const char barr1[7] = "0010010";
const char barr2[7] = "1011011";
const char barr3[7] = "1101101";
const char barr4[7] = "0100100";

// Declaración de cada pieza
// PCA1 - Horas
// ----------- Decimales
uint8_t hora_dec[7] = {0,1,2,3,4,5,6};

uint8_t a1 = 0;
uint8_t b1 = 1;
uint8_t c1 = 2;
uint8_t d1 = 3;
uint8_t e1 = 4;
uint8_t f1 = 5;
uint8_t g1 = 6;
// ----------- Unidades
uint8_t hora_uni[7] = {8,9,10,11,12,13,14};

uint8_t a2 = 8;
uint8_t b2 = 9;
uint8_t c2 = 10;
uint8_t d2 = 11;
uint8_t e2 = 12;
uint8_t f2 = 13;
uint8_t g2 = 14;

// PCA2 - Minutos
// ----------- Decimales
uint8_t minuto_dec[7] = {0,1,2,3,4,5,6};

uint8_t a3 = 0;
uint8_t b3 = 1;
uint8_t c3 = 2;
uint8_t d3 = 3;
uint8_t e3 = 4;
uint8_t f3 = 5;
uint8_t g3 = 6;
// ----------- Unidades
uint8_t minuto_uni[7] = {8,9,10,11,12,13,14};

uint8_t a4 = 8;
uint8_t b4 = 9;
uint8_t c4 = 10;
uint8_t d4 = 11;
uint8_t e4 = 12;
uint8_t f4 = 13;
uint8_t g4 = 14;

int hora;
int minuto;
int tiempo1;
int tiempo2;
long timeStart;
long clockEpoch;

DS3231 clock;
bool h12Flag;
bool pmFlag;

// Botones
int btnHour = 6;
int btnMin = 5;
int buttonState = 0;

void setup() {
  clock.setClockMode(false);  // set to 24h
  Wire.begin();

  Serial.begin(9600);

  pinMode(btnHour, INPUT);
  pinMode(btnMin, INPUT);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pwm2.begin();
  pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(1000);
  animacion();
}

void incrementHour(int i){
    clock.setHour((clock.getHour(h12Flag, pmFlag)+i)%24);
}

void incrementMinute(int i){
    clock.setMinute((clock.getMinute()+i)%60);
}

void loop() {
  updateClockTime(clockEpoch, timeStart);
  buttonState = digitalRead(btnHour);
  if(buttonState == HIGH){
    incrementHour(1);
    delay(500);
    clock.setSecond(0);
  }

  buttonState = digitalRead(btnMin);
  if(buttonState == HIGH){
    incrementMinute(1);
    delay(500);
    clock.setSecond(0);
  }
  delay(10);
}

void animacion(){
  activar_todo();
  delay(500);
  desactivar_todo();
  delay(500);
  barrido();
  delay(200);
  poner_hora(hora_dec,charh);
  delay(200);
  poner_hora(hora_uni,char0);
  delay(200);
  poner_minuto(minuto_dec,charl);
  delay(200);
  poner_minuto(minuto_uni,chara);
  delay(3000);
  }

void barrido(){
  poner_hora(hora_dec,barr1);
  delay(200);
  poner_hora(hora_dec,barr2);
  delay(200);
  poner_hora(hora_dec,barr3);
  delay(200);
  poner_hora(hora_dec,barr4);
  poner_hora(hora_uni,barr1);
  delay(200);
  poner_hora(hora_dec,charEmpty);
  poner_hora(hora_uni,barr2);
  delay(200);
  poner_hora(hora_uni,barr3);
  delay(200);
  poner_hora(hora_uni,barr4);
  poner_minuto(minuto_dec,barr1);
  delay(200);
  poner_hora(hora_uni,charEmpty);
  poner_minuto(minuto_dec,barr2);
  delay(200);
  poner_minuto(minuto_dec,barr3);
  delay(200);
  poner_minuto(minuto_dec,barr4);
  poner_minuto(minuto_uni,barr1);
  delay(200);
  poner_minuto(minuto_dec,charEmpty);
  poner_minuto(minuto_uni,barr2);
  delay(200);
  poner_minuto(minuto_uni,barr3);
  delay(200);
  poner_minuto(minuto_uni,barr4);
  delay(200);
  desactivar_todo();
  delay(600);

}

void barrido_in(){
  desactivar_todo();
  delay(300);
  poner_hora(hora_dec,barr1);
  delay(200);
  poner_hora(hora_dec,barr2);
  delay(200);
  poner_hora(hora_dec,char8);
  delay(200);
  poner_hora(hora_uni,barr1);
  delay(200);
  poner_hora(hora_uni,barr2);
  delay(200);
  poner_hora(hora_uni,char8);
  delay(200);
  poner_minuto(minuto_dec,barr1);
  delay(200);
  poner_minuto(minuto_dec,barr2);
  delay(200);
  poner_minuto(minuto_dec,char8);
  delay(200);
  poner_minuto(minuto_uni,barr1);
  delay(200);
  poner_minuto(minuto_uni,barr2);
  delay(200);
  poner_minuto(minuto_uni,char8);
  delay(800);
}

void barrido_out(){
  activar_todo();
  delay(300);
  poner_hora(hora_dec,barr3);
  delay(200);
  poner_hora(hora_dec,barr4);
  delay(200);
  poner_hora(hora_dec,charEmpty);
  delay(200);
  poner_hora(hora_uni,barr3);
  delay(200);
  poner_hora(hora_uni,barr4);
  delay(200);
  poner_hora(hora_uni,charEmpty);
  delay(200);
  poner_minuto(minuto_dec,barr3);
  delay(200);
  poner_minuto(minuto_dec,barr4);
  delay(200);
  poner_minuto(minuto_dec,charEmpty);
  delay(200);
  poner_minuto(minuto_uni,barr3);
  delay(200);
  poner_minuto(minuto_uni,barr4);
  delay(200);
  poner_minuto(minuto_uni,charEmpty);
  delay(800);
}

void cafe(){
  poner_hora(hora_dec,charc);
  poner_hora(hora_uni,chara);
  poner_minuto(minuto_dec,charf);
  poner_minuto(minuto_uni,chare);
}


void desactivar_todo(){
  poner_minuto(minuto_dec,charEmpty);
  poner_minuto(minuto_uni,charEmpty);
  poner_hora(hora_dec,charEmpty);
  poner_hora(hora_uni,charEmpty);
}

void activar_todo(){
  poner_minuto(minuto_dec,char8);
  poner_minuto(minuto_uni,char8);
  poner_hora(hora_dec,char8);
  poner_hora(hora_uni,char8);
}

void poner_minuto(uint8_t cifra[7],char valor[7]){
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
      if (valor[6-i]=='0'){
        pwm.setPWM(cifra[i], 0, pos270);
      }
      else{
        pwm.setPWM(cifra[i], 0, pos0);
      }
    }
    else{
      if (valor[6-i]=='0'){
        pwm.setPWM(cifra[i], 0, pos90);
      }
      else{
        pwm.setPWM(cifra[i], 0, SERVOMIN);
      }
    }

  }
}

void poner_hora(uint8_t cifra[7],char valor[7]){
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
      if (valor[6-i]=='0'){
        pwm2.setPWM(cifra[i], 0, pos270);
      }
      else{
        pwm2.setPWM(cifra[i], 0, pos0);
      }
    }
    else{
      if (valor[6-i]=='0'){
        pwm2.setPWM(cifra[i], 0, pos90);
      }
      else{
        pwm2.setPWM(cifra[i], 0, SERVOMIN);
      }
    }

  }
}

void translate_min(uint8_t cifra[7],int num){
  switch (num) {
  case 0:
    poner_minuto(cifra,char0);
    break;
  case 1:
    poner_minuto(cifra,char1);
    break;
  case 2:
    poner_minuto(cifra,char2);
    break;
  case 3:
    poner_minuto(cifra,char3);
    break;
  case 4:
    poner_minuto(cifra,char4);
    break;
  case 5:
    poner_minuto(cifra,char5);
    break;
  case 6:
    poner_minuto(cifra,char6);
    break;
  case 7:
    poner_minuto(cifra,char7);
    break;
  case 8:
    poner_minuto(cifra,char8);
    break;
  case 9:
    poner_minuto(cifra,char9);
    break;
  default:
    break;
  }
}

void translate_hora(uint8_t cifra[7],int num){
  switch (num) {
  case 0:
    poner_hora(cifra,char0);
    break;
  case 1:
    poner_hora(cifra,char1);
    break;
  case 2:
    poner_hora(cifra,char2);
    break;
  case 3:
    poner_hora(cifra,char3);
    break;
  case 4:
    poner_hora(cifra,char4);
    break;
  case 5:
    poner_hora(cifra,char5);
    break;
  case 6:
    poner_hora(cifra,char6);
    break;
  case 7:
    poner_hora(cifra,char7);
    break;
  case 8:
    poner_hora(cifra,char8);
    break;
  case 9:
    poner_hora(cifra,char9);
    break;
  default:
    break;
  }
}

void updateClockTime(long clockEpoch, long timeStart){
    int currentMinute = clock.getMinute();
    int minutesDigits0 = currentMinute % 10;
    int minutesDigits1 = (currentMinute / 10) % 10;

    int currentHour = clock.getHour(h12Flag, pmFlag);
    int hoursDigits0 = currentHour % 10;
    int hoursDigits1 = (currentHour / 10) % 10;

    translate_min(minuto_uni, minutesDigits0);
    translate_min(minuto_dec, minutesDigits1);
    translate_hora(hora_uni, hoursDigits0);
    translate_hora(hora_dec, hoursDigits1);
}
