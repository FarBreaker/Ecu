#include <Servo.h>
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

#define frontLights 13
#define rearLights 5

const unsigned long BAUD_RATE = 9600;

Servo esc;
Servo servo;

const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;
const long interval = 1000;
unsigned long previousMillis = 0;
bool state = false;

bool isOn = false;
bool lightsOn = false;
int throttle, steering, button;


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
  esc.writeMicroseconds(1000);
  pinMode(frontLights, OUTPUT);
  pinMode(rearLights, OUTPUT);
  Serial.println("setup complete");
}

// Put your main code here, to run repeatedly:
void loop() {
  button = phone.getButton();

  
  
  startEngine();
  if (isOn)
  {
    engine();
  } else
  {
    esc.writeMicroseconds(1000);
  }
  lights();
}

void engine()
{
  throttle = phone.getThrottle();
  steering = phone.getSteering();

  throttle = map(throttle, 0, 99, 1000, 2000);
  steering = map(steering, 0, 99, 135, 60);

  Serial.println(throttle);
  Serial.println(steering);

  esc.writeMicroseconds(throttle);
  servo.write(steering);
}

void startEngine()
{
  if (button == 1 && isOn)
  {
    isOn = !isOn;
  } else if (button == 1 && !isOn)
  {
    isOn = !isOn;
  }
}

void lights()
{
  if (button == 2 && lightsOn)
  {
    lightsOn = !lightsOn;
  } else if (button == 2 && !lightsOn)
  {
    lightsOn = !lightsOn;
  }

  if (lightsOn)
  {
    digitalWrite(frontLights, HIGH);
    timer();
  }else
  {
    digitalWrite(frontLights,LOW);
    digitalWrite(rearLights,LOW);
  }
}

void timer()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    digitalWrite(rearLights, !state);
  }
}
