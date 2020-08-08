
#include <Servo.h>
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

const unsigned long BAUD_RATE = 9600;

Servo esc;
Servo servo;

const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

int prevThrottle = 49;
int prevSteering = 49;
int throttle, steering;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor

// Setup code runs once after program starts.
void setup() {
  // Start serial communications.
  // The baud rate must be the same for both the serial and the bluetooth.
  Serial.begin(BAUD_RATE);
  bluetooth.begin(BAUD_RATE);
  delay(100);
  esc.attach(10);
  servo.attach(9);
  Serial.println("setup complete");
}

// Put your main code here, to run repeatedly:
void loop() {

  // Throttle and steering values go from 0 to 99.
  // When throttle and steering values are at 99/2 = 49, the joystick is at center.
  throttle = phone.getThrottle();
  steering = phone.getSteering();
  throttle = map(throttle, 0, 99, 1000, 2000);
  steering = map(steering, 0, 99, 135, 60);
  Serial.println(throttle);
  Serial.println(steering);
  esc.writeMicroseconds(throttle);
  servo.write(steering);
}
