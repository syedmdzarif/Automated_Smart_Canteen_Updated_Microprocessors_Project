#include <Servo.h>
Servo servo_lid;
Servo servo_shoot;
Servo servo_door;

const int echoPin = 13;
const int trigPin = 12;

const int led_dust_full = 2;
const int led_ldr = 11;
const int led_piezo = 6;

const int ir_lid_in = 9;
const int ir_lid_out = 8;   //conn to this

const int servo_lid_ = 7;

long duration;
int distance;
int safetyDistance;
int irDistance;
int trigger_distance;

#define ir_door 2;

int light;
int piezo_value;

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(HIGH, 1);
  digitalWrite(1, HIGH);

  pinMode(ir_door_in, OUTPUT);
  pinMode(ir_door_out, INPUT);
  
  pinMode(led_ldr, OUTPUT);
  pinMode(led_piezo, OUTPUT);
  pinMode(led_dust_full, OUTPUT);
  digitalWrite(11, LOW);
  digitalWrite(6, LOW);
  digitalWrite(led_dust_full, LOW);
  

  Serial.begin(9600);
}
void loop(){
  

  light = analogRead(A0);   //ldr connect to resistor one end, other end directly to 5v, one end to A0, resistor other end to gnd
  piezo_value = analogRead(A1);   //piezo connect to A1 AND ground
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 50){
    digitalWrite(led_piezo, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(led_piezo, LOW);
    //delay(1000);
  }
  
  if(light > 40){
    digitalWrite(led_ldr, LOW);
    //delay(1000);
  }
  else{
    digitalWrite(led_ldr, HIGH);
    //delay(1000);
  }
  
}
