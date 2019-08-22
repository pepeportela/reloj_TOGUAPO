// TODO: Crear una flag de activación de los movimientos de los servos. Si esta desactivada los servos no se mueven pero el programa sigue en ejecución. Ideal para las noches y mostrar mensajes.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Este es el PCA principal con default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire,0x40);
// esta será la direccion del PCA esclavo/puenteado  TODO: Soldar los pines del PCA
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire,0x41);

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

// Declaración de cada pieza
// PCA1 - Horas
// ----------- Decimales
uint8_t hora_dec[7] = {5,4,6,3,2,1,0};

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

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  pwm2.begin();
  pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(2,INPUT);
  animacion();

  hora = 48;
  minuto = 0;
  


}

void animacion(){
  activar_todo();
  delay(500);
  desactivar_todo();
  delay(500);
  poner_hora(hora_dec,charh);
  delay(200);
  poner_hora(hora_uni,char0);
  delay(200);
  poner_minuto(minuto_dec,charl);
  delay(200);
  poner_minuto(minuto_dec,chara);
  delay(3000);
  }

void cafe(){
//  activar_todo();
//  delay(200);
//  desactivar_todo();
//  delay(500);
//  hora_decena(charc);
//  delay(700);
//  hora_unidad(chara);
//  delay(700);
//  poner_minuto(minuto_dec,charf);
//  delay(700);
//  minuto_unidad(chare);
//  delay(2000);
  }


void desactivar_todo(){
  poner_minuto(minuto_dec,charEmpty);
  poner_minuto(minuto_uni,charEmpty);
  poner_hora(minuto_dec,charEmpty);
  poner_hora(minuto_uni,charEmpty);

  // pwm.setPWM(a3, 0, pos90);
  // pwm.setPWM(b3, 0, pos90);
  // pwm.setPWM(c3, 0, pos270);
  // pwm.setPWM(d3, 0, pos270);
  // pwm.setPWM(e3, 0, pos270);
  // pwm.setPWM(f3, 0, pos90);
  // pwm.setPWM(g3, 0, pos90-60);

}

void activar_todo(){
  poner_minuto(minuto_dec,char8);
  poner_minuto(minuto_uni,char8);
  poner_hora(minuto_dec,char8);
  poner_hora(minuto_uni,char8);
  // pwm.setPWM(a3, 0, SERVOMIN);
  // pwm.setPWM(b3, 0, SERVOMIN);
  // pwm.setPWM(c3, 0, pos0);
  // pwm.setPWM(d3, 0, pos0);
  // pwm.setPWM(e3, 0, pos0);
  // pwm.setPWM(f3, 0, SERVOMIN);
  // pwm.setPWM(g3, 0, SERVOMIN);
}

void loop() {
 delay(59000);
 if( minuto==0 && hora==0){
   activar_todo();
   delay(200);
   desactivar_todo();
   delay(200);
 }
 else if(minuto==0){
   minuto=59;
   hora=-1;
 }
 else{
   minuto=-1;
 }
 int num = minuto/10;
 translate_min(minuto_dec,num);
 num = minuto - (num*10);
 translate_min(minuto_uni,num);
 // Mostrar hora
 num = hora/10;
 translate_hora(hora_dec,num);
 num = hora - (num*10);
 translate_hora(hora_uni,num);
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
void llamada_animacion(){
  animacion();
}
