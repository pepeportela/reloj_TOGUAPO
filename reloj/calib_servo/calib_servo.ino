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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {
  delay(2000);
  // put your main code here, to run repeatedly:
  pwm.setPWM(2, 0, 2*SERVOMAX/3);
  delay(1000);
  Serial.print("1");
  pwm.setPWM(2, 0, SERVOMIN/2);
  delay(1000);
  pwm.setPWM(2, 0, 0);
  delay(1000);
  Serial.print("2");
  
}
