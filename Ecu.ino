#define throttle A0  //Should be A0
#define steering A1  //should be A1
#define esc 10
#define steer 9

#include <Servo.h>

Servo engine;
Servo steerServo;

void setup() {
  // put your setup code here, to run once:
  engine.attach(esc);
  steerServo.attach(steer);
  
  engine.writeMicroseconds(1000);
  steerServo.write(45);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int engVal;
  int steerVal;
  steerVal = analogRead(steering);
  engVal = analogRead(throttle);
  
  steerVal = map(steerVal, 0, 1023, 60, 120);
  engVal = map(engVal, 0, 1023, 1000, 2000);
  engine.writeMicroseconds(engVal);
  steerServo.write(steerVal);
  Serial.println(engVal);
  Serial.println(steerVal);

}
