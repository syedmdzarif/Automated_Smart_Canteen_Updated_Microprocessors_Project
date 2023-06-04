#include <Wire.h> 
#include <Servo.h> 
#include <MFRC522.h>

//Servo
Servo servo1;
//Servo servo_ramp;

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int ir1out = 7;
int ir2out = 6;


int light;
int piezo_value;

void setup() {
  
  
  SPI.begin();      // Initiate  SPI bus

  //IR
  pinMode(ir1out, INPUT);
  pinMode(ir2out, INPUT);

  //RFID
  mfrc522.PCD_Init();   // Initiate MFRC522

  //Servo
  servo1.attach(5);
  servo1.write(0);
  //servo_ramp.attach(3);
  //servo_ramp.write(0);


  //ldr piezo

  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);


  Serial.begin(9600);   // Initiate a serial communication
}

void loop(){
   
 
  

  light = analogRead(A0);
  piezo_value = analogRead(A1);
  Serial.println("LDR:");
  Serial.println(light);
  Serial.println("Peizo:");
  Serial.println(piezo_value);
  //delay(1000);

  if(piezo_value > 100){
    digitalWrite(4, HIGH);
    //digitalWrite(3, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(4, LOW);
    //digitalWrite(3, HIGH);
    //delay(1000);
  }
  
  if(light > 100){
    digitalWrite(2, LOW);
    //digitalWrite(3, HIGH);
    //delay(1000);
  }
  else{
    digitalWrite(2, HIGH);
    //digitalWrite(3, HIGH);
    //delay(1000);
  }

  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
    
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
    
  }
  
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     
  }
  Serial.println();
  content.toUpperCase();



  if (content.substring(1) == "93 F1 C3 0B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Message : Authorized access");


    Serial.print("ir1 : ");
    Serial.println(digitalRead(ir1out));
    Serial.print("ir2 : ");
    Serial.println(digitalRead(ir2out));
    //digitalWrite(3, HIGH);
    
    if (digitalRead(ir1out)==0 && digitalRead(ir2out)==1){
      servo1.write(90);
      delay(1000);
      servo1.write(0);
      //digitalWrite(3, HIGH);
    }
    else if (digitalRead(ir1out)==0 && digitalRead(ir2out)==0){
      servo1.write(90);
      delay(3000);
      servo1.write(0);
      //digitalWrite(3, HIGH);
    }
  
  
  }
 else   {
    
    Serial.println(" Access denied");
    //digitalWrite(3, HIGH);
  }
  servo1.write(0);
  //digitalWrite(3, HIGH);
}
