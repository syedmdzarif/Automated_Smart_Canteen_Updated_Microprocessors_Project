void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A1);
  Serial.println(value);

  if(value > 50){
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
  }

}
