

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// Declaración de cada pieza
// PCA2
uint8_t a1 = 0;
uint8_t b1 = 1;
uint8_t c1 = 2;
uint8_t d1 = 3;
uint8_t e1 = 4;
uint8_t f1 = 5;
uint8_t g1 = 6;
uint8_t a2 = 8;
uint8_t b2 = 9;
uint8_t c2 = 10;
uint8_t d2 = 11;
uint8_t e2 = 12;
uint8_t f2 = 13;
uint8_t g2 = 14;

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
  Serial.println(servonum);
  pwm.setPWM(servonum, 0, 2*SERVOMAX/3);
  delay(500);
  pwm.setPWM(servonum, 0, SERVOMIN);
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//    pwm.setPWM(servonum, 0, SERVOMIN);
//  }
//
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum, 0, SERVOMAX/2);
//  }

  delay(500);

  servonum ++;
  if (servonum > 7) servonum = 0;
}
