#include <WiFi.h>
#include <Servo.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above




Servo servo1;
Servo servo2;

int bill = 0;

String output34State = "off";
String output35State = "off";
String output32State = "off";
String output33State = "off";


// Replace with your network credentials
const char* ssid = "Net";
const char* password = "123123123";

// Set web server port number to 80
WiFiServer server(80);

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state


String output13State = "off";
String output27State = "off";




// Assign output variables to GPIO pins
const int output13 = 13;
const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  //pinMode(output26, OUTPUT);
  //pinMode(output27, OUTPUT);
  // Set outputs to LOW
  //digitalWrite(output26, LOW);
  //digitalWrite(output27, LOW);
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  //rfid

  
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
 
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);

  
servo1.attach(13);
servo2.attach(27);
servo1.write(0);
servo2.write(0);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){

   //rfid

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

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


  


  //rfid


  

 
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.print("HELLO WORLD");
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();




           


            

  

            //items


            if (header.indexOf("GET /34") >= 0) {    //item 1 rice = 30
              //Serial.println("GPIO 13 on");
              //output13State = "on";
              //digitalWrite(output26, HIGH);
              //servo1.write(90);
              //delay(1000);
              //servo1.write(0);
              bill = bill + 30;
              digitalWrite(34, HIGH);
              delay(10000);
              digitalWrite(34, HIGH);
              client.println(bill);
            } 
            if (header.indexOf("GET /35") >= 0) {    //item 2 curry = 100
              //Serial.println("GPIO 13 on");
              //output13State = "on";
              //digitalWrite(output26, HIGH);
              //servo1.write(90);
              //delay(1000);
              //servo1.write(0);
              bill = bill + 100;
              digitalWrite(35, HIGH);
              delay(10000);
              digitalWrite(35, HIGH);
              client.println(bill);
            } 
            if (header.indexOf("GET /32") >= 0) {    //item 3 shingara price 10
              //Serial.println("GPIO 13 on");
              //output13State = "on";
              //digitalWrite(output26, HIGH);
              //servo1.write(90);
              //delay(1000);
              //servo1.write(0);
              bill = bill + 10;
              digitalWrite(32, HIGH);
              delay(10000);
              digitalWrite(32, HIGH);
              client.println(bill);
              
            } 
            if (header.indexOf("GET /33") >= 0) {   //item 4 noodles price 50
              //Serial.println("GPIO 13 on");
              //output13State = "on";
              //digitalWrite(output26, HIGH);
              //servo1.write(90);
              //delay(1000);
              //servo1.write(0);
              bill = bill + 50;
              digitalWrite(33, HIGH);
              delay(10000);
              digitalWrite(33, HIGH);
              client.println(bill);
            } 


            //items
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /13") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              //digitalWrite(output26, HIGH);
              servo1.write(90);
              delay(1000);
              servo1.write(0);
            } 
            //else if (header.indexOf("GET /13/off") >= 0) {
                //Serial.println("GPIO 13 off");
              //output13State = "off";
              //digitalWrite(output26, HIGH);
              //servo1.write(90);
              //delay(1000);
             //servo1.write(0);
            //} 
            else if (header.indexOf("GET /27") >= 0) {
             Serial.println("GPIO 27 on");
              output13State = "on";
              //digitalWrite(output26, HIGH);
              servo2.write(90);
              delay(1000);
             servo2.write(0);
            } //else if (header.indexOf("GET /27/off") >= 0) {
              //Serial.println("GPIO 27 off");
              //output13State = "off";
              //digitalWrite(output26, HIGH);
              //servo2.write(90);
              //delay(1000);
             //servo2.write(0);
            //}
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 13 - State " + output13State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }



            //items button

            if (output34State=="off") {
              client.println("<p><a href=\"/34/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/34/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
             if (output35State=="off") {
              client.println("<p><a href=\"/35/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/35/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
             if (output32State=="off") {
              client.println("<p><a href=\"/32/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/32/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
             if (output33State=="off") {
              client.println("<p><a href=\"/33/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/33/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 


            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
