#include <Servo.h>
Servo servo;
Servo servoDoor;
Servo servo_shoot;

//Sonar
const int echoPin = 13;
const int trigPin = 12;

//Signal




//LED CONNECTIONS  **********************************************************

const int ledPin = 3;
//const int buzzer = 10;



  //IR CONNECTIONS  **********************************************************


//IR
const int irIn = 9;
const int irOut = 8;    //conn to this

//
const int ServoIn = 7;


int light;
int piezo_value;

//defines variables
long duration;
int distance;
int safetyDistance;
int irDistance;
int trigger_distance;


//IR DOOR CONNECTIONS  **********************************************************

#define irOutDoor 2

//ldr
#define ldrOUT  A0
//int leddoor = 5;


void setup() {
  //Sonar
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(HIGH, 1);
  digitalWrite(1, HIGH);
  

  //Output
  //pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  //IR - Bin
  pinMode(irIn, OUTPUT);
  pinMode(irOut, INPUT);

  //IR - Door

  //LDR
  //pinMode(leddoor,OUTPUT);

  //Servo
  pinMode(ServoIn, OUTPUT);

  //SERVO CONNECTIONS  **********************************************************
  
  servoDoor.attach(4);
  servo_shoot.attach(5);
  servo.attach(ServoIn);    //7

  
  //SERVO CONNECTIONS  **********************************************************

  servoDoor.write(0);
  servo.write(0);
  servo_shoot.write(0);

  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(11, LOW);
  digitalWrite(6, LOW);
  
  Serial.begin(9600); // Starts the serial communication
}


void loop() {

  light = analogRead(A0);
  piezo_value = analogRead(A1);
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 50){
    digitalWrite(6, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(6, LOW);
    //delay(1000);
  }
  
  if(light > 40){
    digitalWrite(11, LOW);
    //delay(1000);
  }
  else{
    digitalWrite(11, HIGH);
    //delay(1000);
  }

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delay(10);
digitalWrite(trigPin, LOW);



// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

trigger_distance = 4;

  //IR - Door
  if(digitalRead(irOutDoor)==0){
    servoDoor.write(90);
  }
  else{
    servoDoor.write(0);
  }

  

if (distance <= trigger_distance){
  digitalWrite(irIn, LOW);
  digitalWrite(ServoIn, LOW);
  servo.write(0);
  if(digitalRead(irOutDoor)==0){
    servoDoor.write(90);
  }
  else{
    servoDoor.write(0);
  }



  //ldr piezo

  light = analogRead(A0);
  piezo_value = analogRead(A1);
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 50){
    digitalWrite(6, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(6, LOW);
    //delay(1000);
  }
  
  if(light > 40){
    digitalWrite(11, LOW);
    //delay(1000);
  }
  else{
    digitalWrite(11, HIGH);
    //delay(1000);
  }



  //led piezo

  while(distance<=trigger_distance){
    if(digitalRead(irOutDoor)==0){
    servoDoor.write(90);
  }
  else{
    servoDoor.write(0);
  }
  //delay(1000);

  servo_shoot.write(90);


  //ldr piezo

  light = analogRead(A0);
  piezo_value = analogRead(A1);
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 50){
    digitalWrite(6, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(6, LOW);
    //delay(1000);
  }
  
  if(light > 40){
    digitalWrite(11, LOW);
    //delay(1000);
  }
  else{
    digitalWrite(11, HIGH);
    //delay(1000);
  }



  //led piezo

  
    //digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(500);
    //digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
  }
}
else{
  servo_shoot.write(0);

  //ldr piezo

  light = analogRead(A0);
  piezo_value = analogRead(A1);
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 50){
    digitalWrite(6, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(6, LOW);
    //delay(1000);
  }
  
  if(light > 40){
    digitalWrite(11, LOW);
    //delay(1000);
  }
  else{
    digitalWrite(11, HIGH);
    //delay(1000);
  }



  //led piezo
  //digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(irIn, HIGH);
  delay(1000);
  irDistance = digitalRead(irOut);
  
  if (irDistance == 0){
    digitalWrite(ServoIn, HIGH);
    servo.write(90);
    
   }
   else if(irDistance == 1){
    servo.write(0);
    digitalWrite(ServoIn, LOW);
    
   }
  
}

// Prints the distance on the Serial Monitor
Serial.print("IR: ");
Serial.println(irDistance);
Serial.print("Sonar: ");
Serial.println(distance);

}
