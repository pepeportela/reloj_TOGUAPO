

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Este es el PCA principal con default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// esta será la direccion del PCA esclavo/puenteado  TODO: Soldar los pines del PCA
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define pos270  SERVOMAX/2 // this is the 'minimum' pulse length count (out of 4096)
#define pos90 2*SERVOMAX/3 // this is the 'maximum' pulse length count (out of 4096)

const char char1[7] = "0010010";
const char char2[7] = "1011101";

// Declaración de cada pieza
// PCA1 - Horas
// ----------- Decimales
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
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
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
  desactivar_todo();
  }

void desactivar_todo(){
  }
void loop() {
  // Drive each servo one at a time
  pwm.setPWM(a3, 0, pos90);
  delay(500);
  pwm.setPWM(a3, 0, SERVOMIN);

  delay(500);
  pwm.setPWM(c3, 0, pos270);
  delay(500);
  pwm.setPWM(c3, 0, SERVOMIN);

  delay(1000);
  int num = 1;
  minuto_decimal(char1);
  delay(1000);
  minuto_decimal(char2);
}

void minuto_decimal(char valor[7]){
  if (valor[0]=="1"){
    pwm.setPWM(a3, 0, pos90);
  }
  else{
    pwm.setPWM(a3, 0, SERVOMIN);
  }
  if (valor[1]=="1"){
    pwm.setPWM(b3, 0, pos90);
  }
  else{
    pwm.setPWM(b3, 0, SERVOMIN);
  }
  if (valor[2]=="1"){
    pwm.setPWM(c3, 0, pos270);
  }
  else{
    pwm.setPWM(c3, 0, SERVOMIN);
  }
  if (valor[3]=="1"){
    pwm.setPWM(d3, 0, pos270);
  }
  else{
    pwm.setPWM(d3, 0, SERVOMIN);
  }
  if (valor[4]=="1"){
    pwm.setPWM(e3, 0, pos270);
  }
  else{
    pwm.setPWM(e3, 0, SERVOMIN);
  }
  if (valor[5]=="1"){
    pwm.setPWM(f3, 0, pos270);
  }
  else{
    pwm.setPWM(f3, 0, SERVOMIN);
  }
  if (valor[6]=="1"){
    pwm.setPWM(g3, 0, pos270);
  }
  else{
    pwm.setPWM(g3, 0, SERVOMIN);
  }
}
