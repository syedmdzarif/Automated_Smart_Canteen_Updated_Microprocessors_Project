#include <Servo.h>
Servo servo;
Servo servo2;
Servo servo_door;
//Sonar
const int echoPin = 13;
const int trigPin = 12;

//Signal
const int ledPin = 11;
const int buzzer = 2;

//IR
const int irIn = 9;
const int irOut = 8;

//const int irInDoor = 10;
const int irOutDoor = 4;

//servo
const int ServoIn = 7;
const int ServoIn2 = 4;

//defines variables
long duration;
int distance;
int safetyDistance;
int irDistance;
int irDistanceDoor;
int trigger_distance;

void setup() {
  //Sonar
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  //Output
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  //IR
  pinMode(irIn, OUTPUT);
  pinMode(irOut, INPUT);

  //pinMode(irInDoor, OUTPUT);
  pinMode(irOutDoor, INPUT);
  //pinMode(5, HIGH);

  //Servo
  //pinMode(ServoIn, OUTPUT);

  servo.attach(7);
  servo2.attach(6);
  servo_door.attach(5);
  Serial.begin(9600); // Starts the serial communication
}


void loop() {

servo_door.write(0);
//digitalWrite(irInDoor, HIGH);
irDistanceDoor = digitalRead(irOutDoor);
if(irDistanceDoor == 0){
    servo_door.write(0);
    delay(1000);
  
}
else{
    servo_door.write(90);
  
}



// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delay(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

trigger_distance = 10;

if (distance <= trigger_distance){
  digitalWrite(irIn, LOW);
  digitalWrite(ServoIn, LOW);
  servo.write(0);
  servo2.write(90);

  while(distance<=trigger_distance){
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
  }
  servo2.write(0);
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(irIn, HIGH);
  delay(1000);
  irDistance = digitalRead(irOut);
  
  if (irDistance == 0){
    //digitalWrite(ServoIn, HIGH);
    servo.write(90);
    
   }
   else if(irDistance == 1){
    servo.write(0);
    //digitalWrite(ServoIn, LOW);
    
   }
  
}

// Prints the distance on the Serial Monitor
Serial.print("IR: ");
Serial.println(irDistance);
Serial.print("IR Main Door: ");
Serial.println(irDistanceDoor);
Serial.print("Sonar: ");
Serial.println(distance);
}
