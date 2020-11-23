// TODO: Crear una flag de activación de los movimientos de los servos. Si esta desactivada los servos no se mueven pero el programa sigue en ejecución. Ideal para las noches y mostrar mensajes.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <DS3231.h>

// Este es el PCA principal con default address 0x40
Adafruit_PWMServoDriver pwm_min = Adafruit_PWMServoDriver(0x41, Wire);
// esta será la direccion del PCA esclavo/puenteado  TODO: Soldar los pines del PCA
Adafruit_PWMServoDriver pwm_hora = Adafruit_PWMServoDriver(0x40, Wire);

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
int servos_hora_dec_on_0[7] = {pos90, pos90, pos270, pos270, pos270, pos90, pos90};
int servos_hora_dec_on_1[7] = {SERVOMIN, SERVOMIN, pos0, pos0, pos0, SERVOMIN, SERVOMIN};
uint8_t a1 = 0;
uint8_t b1 = 1;
uint8_t c1 = 2;
uint8_t d1 = 3;
uint8_t e1 = 4;
uint8_t f1 = 5;
uint8_t g1 = 6;
// ----------- Unidades
uint8_t hora_uni[7] = {8,9,10,11,12,13,14};
int servos_hora_uni_on_0[7] = {pos90, pos90, pos270, pos270, pos270, pos90, pos90};
int servos_hora_uni_on_1[7] = {SERVOMIN, SERVOMIN+28, pos0, pos0, pos0, SERVOMIN, SERVOMIN};

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
int servos_minuto_dec_on_0[7] = {pos90, pos90, pos270, pos270, pos270, pos90, pos90};
int servos_minuto_dec_on_1[7] = {SERVOMIN, SERVOMIN, pos0, pos0, pos0, SERVOMIN, SERVOMIN};

uint8_t a3 = 0;
uint8_t b3 = 1;
uint8_t c3 = 2;
uint8_t d3 = 3;
uint8_t e3 = 4;
uint8_t f3 = 5;
uint8_t g3 = 6;
// ----------- Unidades
uint8_t minuto_uni[7] = {8,9,10,11,12,13,14};
int servos_minuto_uni_on_0[7] = {pos90, pos90, pos270, pos270, pos270, pos90, pos90};
int servos_minuto_uni_on_1[7] = {SERVOMIN, SERVOMIN, pos0, pos0, pos0, SERVOMIN, SERVOMIN};

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
int btnTemp = 8;
int btnHour = 6;
int btnMin = 5;
int buttonState = 0;

void setup() {
  clock.setClockMode(false);  // set to 24h
  Wire.begin();

  Serial.begin(9600);

  pinMode(btnHour, INPUT);
  pinMode(btnMin, INPUT);

  pwm_min.begin();
  pwm_min.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pwm_hora.begin();
  pwm_hora.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(1000);
  animacion();
}

void incrementHour(int i){
    clock.setHour((clock.getHour(h12Flag, pmFlag)+i)%24);
}

void incrementMinute(int i){
    clock.setMinute((clock.getMinute()+i)%60);
}
void cancaneo(){
  desactivar_todo();
  delay(2000);
  for(i = 0; i < 4; i++){
    delay(190);
    activar_todo();
    delay(190);
    delay(190);
    delay(190);
    desactivar_todo();
    delay(190);
    activar_todo();
    delay(190);
    delay(190);
    desactivar_todo();
    delay(190);
  }
}

void loop() {
  //activar_todo();
  //delay(2000);
  //desactivar_todo();
  //delay(2000);

  buttonState = digitalRead(btnTemp);
  //When button is pressed, mark temperature
  if(buttonState == HIGH){
    //cancaneo();
    int temp = clock.getTemperature();
    int tempUni = temp % 10;
    int tempDec = (temp / 10) % 10;
    poner_hora_dec(translate_to_char(tempDec));
    poner_hora_uni(translate_to_char(tempUni));
    poner_minuto_dec("0001111");
    poner_minuto_uni(charc);
    delay(10000);
  }

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
  poner_hora_dec(charh);
  delay(200);
  poner_hora_uni(char0);
  delay(200);
  poner_minuto_dec(charl);
  delay(200);
  poner_minuto_uni(chara);
  delay(3000);
  }

void barrido(){
  poner_hora_dec(barr1);
  delay(200);
  poner_hora_dec(barr2);
  delay(200);
  poner_hora_dec(barr3);
  delay(200);
  poner_hora_dec(barr4);
  poner_hora_uni(barr1);
  delay(200);
  poner_hora_dec(charEmpty);
  poner_hora_uni(barr2);
  delay(200);
  poner_hora_uni(barr3);
  delay(200);
  poner_hora_uni(barr4);
  poner_minuto_dec(barr1);
  delay(200);
  poner_hora_uni(charEmpty);
  poner_minuto_dec(barr2);
  delay(200);
  poner_minuto_dec(barr3);
  delay(200);
  poner_minuto_dec(barr4);
  poner_minuto_uni(barr1);
  delay(200);
  poner_minuto_dec(charEmpty);
  poner_minuto_uni(barr2);
  delay(200);
  poner_minuto_uni(barr3);
  delay(200);
  poner_minuto_uni(barr4);
  delay(200);
  desactivar_todo();
  delay(600);

}

void barrido_in(){
  desactivar_todo();
  delay(300);
  poner_hora_dec(barr1);
  delay(200);
  poner_hora_dec(barr2);
  delay(200);
  poner_hora_dec(char8);
  delay(200);
  poner_hora_uni(barr1);
  delay(200);
  poner_hora_uni(barr2);
  delay(200);
  poner_hora_uni(char8);
  delay(200);
  poner_minuto_dec(barr1);
  delay(200);
  poner_minuto_dec(barr2);
  delay(200);
  poner_minuto_dec(char8);
  delay(200);
  poner_minuto_uni(barr1);
  delay(200);
  poner_minuto_uni(barr2);
  delay(200);
  poner_minuto_uni(char8);
  delay(800);
}

void barrido_out(){
  activar_todo();
  delay(300);
  poner_hora_dec(barr3);
  delay(200);
  poner_hora_dec(barr4);
  delay(200);
  poner_hora_dec(charEmpty);
  delay(200);
  poner_hora_uni(barr3);
  delay(200);
  poner_hora_uni(barr4);
  delay(200);
  poner_hora_uni(charEmpty);
  delay(200);
  poner_minuto_dec(barr3);
  delay(200);
  poner_minuto_dec(barr4);
  delay(200);
  poner_minuto_dec(charEmpty);
  delay(200);
  poner_minuto_uni(barr3);
  delay(200);
  poner_minuto_uni(barr4);
  delay(200);
  poner_minuto_uni(charEmpty);
  delay(800);
}

void cafe(){
  poner_hora_dec(charc);
  poner_hora_uni(chara);
  poner_minuto_dec(charf);
  poner_minuto_uni(chare);
}


void desactivar_todo(){
  poner_minuto_dec(charEmpty);
  poner_minuto_uni(charEmpty);
  poner_hora_dec(charEmpty);
  poner_hora_uni(charEmpty);
}

void activar_todo(){
  poner_minuto_dec(char8);
  poner_minuto_uni(char8);
  poner_hora_dec(char8);
  poner_hora_uni(char8);
}

void poner_digito(Adafruit_PWMServoDriver pwm, uint8_t cifra[7], char valor[7], int servo_on_0[7], int servo_on_1[7]){
  for (int i=0; i<7; i++){
    if (valor[6-i]=='0'){
      pwm.setPWM(cifra[i], 0, servo_on_0[i]);
    }
    else {
      pwm.setPWM(cifra[i], 0, servo_on_1[i]);
    }
  }
}

void poner_minuto_dec(char valor[7]){
    poner_digito(pwm_min, minuto_dec, valor, servos_minuto_dec_on_0, servos_minuto_dec_on_1);
}
void poner_minuto_uni(char valor[7]){
    poner_digito(pwm_min, minuto_uni, valor, servos_minuto_uni_on_0, servos_minuto_uni_on_1);
}
void poner_hora_dec(char valor[7]){
    poner_digito(pwm_hora, hora_dec, valor, servos_hora_dec_on_0, servos_hora_dec_on_1);
}
void poner_hora_uni(char valor[7]){
    poner_digito(pwm_hora, hora_uni, valor, servos_hora_uni_on_0, servos_hora_uni_on_1);
}

char * translate_to_char(int num){
  switch (num) {
  case 0:
    return char0;
  case 1:
    return char1;
  case 2:
    return char2;
  case 3:
    return char3;
  case 4:
    return char4;
  case 5:
    return char5;
  case 6:
    return char6;
  case 7:
    return char7;
  case 8:
    return char8;
  case 9:
    return char9;
  default:
    return charEmpty;
  }
}

void updateClockTime(long clockEpoch, long timeStart){
    int currentMinute = clock.getMinute();
    int minutesDigits0 = currentMinute % 10;
    int minutesDigits1 = (currentMinute / 10) % 10;

    int currentHour = clock.getHour(h12Flag, pmFlag);
    int hoursDigits0 = currentHour % 10;
    int hoursDigits1 = (currentHour / 10) % 10;

    poner_minuto_dec(translate_to_char(minutesDigits1));
    poner_minuto_uni(translate_to_char(minutesDigits0));
    poner_hora_dec(translate_to_char(hoursDigits1));
    poner_hora_uni(translate_to_char(hoursDigits0));
}
