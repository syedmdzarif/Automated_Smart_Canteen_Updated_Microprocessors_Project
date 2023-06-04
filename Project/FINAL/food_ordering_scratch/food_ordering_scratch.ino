
// Load Wi-Fi library
#include <WiFi.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Replace with your network credentials
//const char* ssid = "Net";
//const char* password = "123123123";
const char* ssid = "CHAMBER";
const char* password = "shadot16210";
const char* host = "localhost";

// Set web server port number to 80
WiFiServer server(80);

String ID;
int bill = 0;
String items = "";
int table_no;



// Variable to store the HTTP request
String header;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;



// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";
String output32State = "off";

String table1 = "off";
String table2 = "off";
String table3 = "off";



// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;
const int output32 = 32;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);


   //rfid

  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));



   //rfid end


  
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output32, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output32, LOW);

  
  servo1.attach(13);
  servo2.attach(33);
  servo3.attach(12);
  //servo4.attach(14);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  //servo4.write(0);


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
            //return;
            //bill = 0;
            
            }
            

            // Select one of the cards
            if ( ! mfrc522.PICC_ReadCardSerial()) {
            //return;
            //bill = 0;
            
             }
             

            // Dump debug info about the card; PICC_HaltA() is automatically called
             //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

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

            ID = content.substring(1);

           

  


  //rfid
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
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

            if(ID!= NULL){
              client.println("http://192.168.43.22/");
            }


   
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26") >= 0) {   //fried rice 80
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
              delay(5000);
              digitalWrite(output26, LOW);
              bill = bill + 80;
              items = items + ", fried rice";
            }
            if (header.indexOf("GET /27") >= 0) {   //burger 60
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
              delay(5000);
              digitalWrite(output27, LOW);
              bill = bill + 60;
            } 
         
             if (header.indexOf("GET /32") >= 0) {    //noodles 50
              Serial.println("GPIO 32 on");
              output32State = "on";
              digitalWrite(output32, HIGH);
              delay(5000);
              digitalWrite(output32, LOW);
              bill = bill + 50;
            } 

            //table select

            if (header.indexOf("GET /table1") >= 0) {
              bill = 0;
              table_no = 1;
              table1 = "on";
              servo1.write(180);
              delay(5000);
              servo1.write(0);
              delay(1000);
              
            }

            if (header.indexOf("GET /table2") >= 0) {
              bill = 0;
              table_no = 2;
              table1 = "on";
              table2 = "on";
              servo1.write(180);
              delay(1000);
              servo2.write(180);
              delay(1000);
              delay(5000);
              servo2.write(0);
              delay(1000);
              servo1.write(0);
              delay(1000);
              

              
              
              
              //servo2.write(180);
              //delay(1000);
              //servo2.write(0);

              
            }

            if (header.indexOf("GET /table3") >= 0) {
              bill = 0;
              table_no = 3;
              table1 = "on";
              table2 = "on";
              table3 = "on";
              servo1.write(180);
              delay(1000);
              servo2.write(180);
              delay(1000);
              servo3.write(180);
              delay(1000);
              delay(5000);
              servo3.write(0);
              delay(1000);
              servo2.write(0);
              delay(1000);
              servo1.write(0);
              delay(1000);

              

              //servo3.write(180);
              //delay(1000);
              //servo3.write(0);
            }

  
            
            
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
            client.println("<body><h1>Smart Canteen System</h1>");
            client.println("<body><h2>Student ID: </h2>");
            client.println(ID);
            client.println("<body><h2>Total Bill: </h2>");
            client.println(bill);
            client.println("<h4>BDT</h4>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Fried Rice - 80 BDT</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26\"><button class=\"button\">Add Item</button></a></p>");
            } else {
              client.println("<p><a href=\"/26\"><button class=\"button\">Add Item</button></a></p>");
            } 
            
            client.println("<p>Burger - 60 BDT</p>");
            if (output32State=="off") {
              client.println("<p><a href=\"/32\"><button class=\"button\">Add Item</button></a></p>");
            } else {
              client.println("<p><a href=\"/32\"><button class=\"button\">Add Item</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Noodles - 50 BDT</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27\"><button class=\"button\">Add Item</button></a></p>");
            } else {
              client.println("<p><a href=\"/27\"><button class=\"button\">Add Item</button></a></p>");
            }






            client.println("<body><h2>Please select your table</h2>");
            client.println("<p>Table Number 1</p>");
             if (table1=="off") {
              client.println("<p><a href=\"/table1\"><button class=\"button\">Table-1</button></a></p>");
            } else {
              client.println("<p><a href=\"/table1\"><button class=\"button\">Table-1</button></a></p>");
            }
              client.println("<p>Table Number 2</p>");
             if (table2=="off") {
              client.println("<p><a href=\"/table2\"><button class=\"button\">Table-2</button></a></p>");
            } else {
              client.println("<p><a href=\"/table2\"><button class=\"button\">Table-2</button></a></p>");
            }
            client.println("<p>Table Number 3</p>");
             if (table3=="off") {
              client.println("<p><a href=\"/table3\"><button class=\"button\">Table-3</button></a></p>");
            } else {
              client.println("<p><a href=\"/table3\"><button class=\"button\">Table-3</button></a></p>");
            }



            //DB_CONN
            client.print(String("GET http://localhost/micro_smart_canteen/connect.php?") + ("&student_id=") + ID + ("$items=") + items + ("$table_no=") + table_no + ("$bill=") + bill + "HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 


            //DB_CONN END
      




            
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
