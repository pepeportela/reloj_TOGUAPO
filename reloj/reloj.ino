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
uint8_t hora_dec[7] = {0,1,2,3,4,5,6};

uint8_t a1 = 0;
uint8_t b1 = 1;
uint8_t c1 = 2;
uint8_t d1 = 3;
uint8_t e1 = 4;
uint8_t f1 = 5;
uint8_t g1 = 6;
// ----------- Unidades 

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
uint8_t a4 = 8;
uint8_t b4 = 9;
uint8_t c4 = 10;
uint8_t d4 = 11;
uint8_t e4 = 12;
uint8_t f4 = 13;
uint8_t g4 = 14;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(2,INPUT);
  animacion();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void animacion(){
  activar_todo();
  delay(200);
  desactivar_todo();
  delay(500);
  hora_decena(charh);
  delay(700);
  hora_unidad(char0);
  delay(700);
  poner_char(minuto_dec,charl);
  delay(700);
  minuto_unidad(chara);
  delay(2000);
  }

void cafe(){
  activar_todo();
  delay(200);
  desactivar_todo();
  delay(500);
  hora_decena(charc);
  delay(700);
  hora_unidad(chara);
  delay(700);
  poner_char(minuto_dec,charf);
  delay(700);
  minuto_unidad(chare);
  delay(2000);
  }


void desactivar_todo(){
  pwm.setPWM(a3, 0, pos90);
  pwm.setPWM(b3, 0, pos90);
  pwm.setPWM(c3, 0, pos270);
  pwm.setPWM(d3, 0, pos270);
  pwm.setPWM(e3, 0, pos270);
  pwm.setPWM(f3, 0, pos90);
  pwm.setPWM(g3, 0, pos90-60);

}

void activar_todo(){
  pwm.setPWM(a3, 0, SERVOMIN);
  pwm.setPWM(b3, 0, SERVOMIN);
  pwm.setPWM(c3, 0, pos0);
  pwm.setPWM(d3, 0, pos0);
  pwm.setPWM(e3, 0, pos0);
  pwm.setPWM(f3, 0, SERVOMIN);
  pwm.setPWM(g3, 0, SERVOMIN);
}

void loop() {

  activar_todo();
  delay(1000);
  poner_char(minuto_dec,char9);
  delay(1000);
  poner_char(minuto_dec,char8);
  delay(1000);
  poner_char(minuto_dec,char7);
  delay(1000);
  poner_char(minuto_dec,char6);
  delay(1000);
  poner_char(minuto_dec,char5);
  delay(1000);
  poner_char(minuto_dec,char4);
  delay(1000);
  poner_char(minuto_dec,char3);
  delay(1000);
  poner_char(minuto_dec,char2);
  delay(1000);
  poner_char(minuto_dec,char1);
  delay(1000);
  poner_char(minuto_dec,char0);
  delay(1000);
  
  activar_todo();
  for (int i=0;i<60;i++){
    if (digitalRead(2)==LOW){
      animacion();
    }
    else{
      activar_todo();
      delay(1000);
    }
  }

}

void poner_char(uint8_t cifra[7],char valor[7]){
  for (int i=0; i<7; i++){
    if (cifra[i]>=2 && cifra[i]<=4){
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

void llamada_animacion(){
  animacion();
}

void hora_decena(char valor[7]){
}
void hora_unidad(char valor[7]){
}
void minuto_unidad(char valor[7]){
}
