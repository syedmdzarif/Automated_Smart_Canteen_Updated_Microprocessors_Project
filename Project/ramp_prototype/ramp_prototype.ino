#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
int num;

void setup() {

  servo1.attach(7);
  servo2.attach(6);
  servo3.attach(5);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);

  Serial.begin(9600);
 

}

void loop() {
  if(Serial.available()){
    num =  Serial.parseInt();
    
  }

  

  if(num == 1){
  servo1.write(180);
  delay(1000);
  servo2.write(180);
  delay(1000);
  servo3.write(180);
  delay(1000);

  delay(5000);

  servo1.write(0);
  delay(1000);
  servo2.write(0);
  delay(1000);
  servo3.write(0);
  delay(1000);


  

  }

  else if(num == 2){
  servo1.write(180);
  delay(1000);
  servo2.write(180);
  delay(1000);

   delay(5000);
  

  servo1.write(0);
  delay(1000);
  servo2.write(0);
  delay(1000);
  }


  else if(num == 3){
  servo1.write(180);
  delay(1000);

   delay(5000);
 
  

  servo1.write(0);
  delay(1000);
 
  }

}
