#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
// you can also call it with a different address you want
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41, Wire);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

#define pos0  SERVOMIN*2
#define pos270  2*SERVOMIN/3 // this is the 'minimum' pulse length count (out of 4096)
#define pos90 2*SERVOMAX/3 // this is the 'maximum' pulse length count (out of 4096)

uint8_t hora_dec[7] = {0,1,2,3,4,5,6};
uint8_t hora_uni[7] = {8,9,10,11,12,13,14};
uint8_t minuto_dec[7] = {0,1,2,3,4,5,6};
uint8_t minuto_uni[7] = {8,9,10,11,12,13,14};

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();
  //pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency
  pwm2.begin();
  //pwm2.setOscillatorFrequency(27000000);
  pwm2.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(3000);
}

void loop() {
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
        pwm.setPWM(hora_dec[i], 0, pos270);
        delay(1000);
        pwm.setPWM(hora_dec[i], 0, pos0);
        delay(1000);
    }
    else{
        pwm.setPWM(hora_dec[i], 0, pos90);
        delay(1000);
        pwm.setPWM(hora_dec[i], 0, SERVOMIN);
        delay(1000);
    }
  }
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
        pwm.setPWM(hora_uni[i], 0, pos270);
        delay(1000);
        pwm.setPWM(hora_uni[i], 0, pos0);
        delay(1000);
    }
    else{
        pwm.setPWM(hora_uni[i], 0, pos90);
        delay(1000);
        pwm.setPWM(hora_uni[i], 0, SERVOMIN);
        delay(1000);
    }
  }
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
        pwm2.setPWM(minuto_dec[i], 0, pos270);
        delay(1000);
        pwm2.setPWM(minuto_dec[i], 0, pos0);
        delay(1000);
    }
    else{
        pwm2.setPWM(minuto_dec[i], 0, pos90);
        delay(1000);
        pwm2.setPWM(minuto_dec[i], 0, SERVOMIN);
        delay(1000);
    }
  }
  for (int i=0; i<7; i++){
    if (i>=2 && i<=4){
        pwm2.setPWM(minuto_uni[i], 0, pos270);
        delay(1000);
        pwm2.setPWM(minuto_uni[i], 0, pos0);
        delay(1000);
    }
    else{
        pwm2.setPWM(minuto_uni[i], 0, pos90);
        delay(1000);
        pwm2.setPWM(minuto_uni[i], 0, SERVOMIN);
        delay(1000);
    }
  }
}