#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
//Servo servo4;
char data = 0; //Variable for storing received data 
void setup() 
{ 
 Serial.begin(9600); //Sets the data rate in bits per second (baud) for serial data transmission 
 //pinMode(13, OUTPUT); //Sets digital pin 13 as output pin 
 servo1.attach(4);
 servo2.attach(8);
 servo3.attach(3);
 //servo4.attach();

 servo1.write(0);
 servo2.write(0);
 servo3.write(0);
 //servo4.write(0);
} 
void loop() 
{ 
 if(Serial.available() > 0) // Send data only when you receive data: 
 { 
 data = Serial.read(); //Read the incoming data and store it into variable data 
 Serial.write(data); //Print Value inside data in Serial monitor 
 Serial.print("\n"); //New line 
 
 if(data == '1') //Checks whether value of data is equal to 1 
 { 
 //digitalWrite(13, HIGH); //If value is 1 then LED turns ON 
 servo1.write(90);
 delay(1000);
 servo1.write(0);
 
 Serial.write("arduno: message received "); 
 Serial.write(data); 
 Serial.print("\n"); //New line 
 Serial.write("arduno: Servo is ON"); 
 } 
 else if(data == '2') //Checks whether value of data is equal to 0 
 { 
 //digitalWrite(13, LOW); //If value is 0 then LED turns OFF 
 servo2.write(90);
 delay(1000);
 servo2.write(0);
 Serial.write("arduno: message received "); 
 Serial.write(data); 
 Serial.print("\n"); //New line 
 Serial.write("arduno: SERVO is ON"); 
 
 }

  else if(data == '3') //Checks whether value of data is equal to 0 
 { 
 //digitalWrite(13, LOW); //If value is 0 then LED turns OFF 
 servo3.write(90);
 delay(1000);
 servo3.write(0);
 Serial.write("arduno: message received "); 
 Serial.write(data); 
 Serial.print("\n"); //New line 
 Serial.write("arduno: SERVO is ON"); 
 } 

 
 } 
 
}
