int light;
int piezo_value;

void setup(){
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(11, LOW);
  digitalWrite(6, LOW);

  Serial.begin(9600);
}
void loop(){

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
  
}
