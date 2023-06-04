#include <Servo.h>
Servo servo;
const int analogPin = A0;
int sensorValue = 0;
int servoPin = 5;


void setup() {
  // put your setup code here, to run once:
  
  servo.attach(servoPin);

  

  //Serial.begin(9600);
  

}

void loop() {
  sensorValue = analogRead(analogPin);
  servo.write(0);

  if(sensorValue < 600){
      servo.write(90);
      delay(100);
  }
  else{
      servo.write(0);
  }

}
