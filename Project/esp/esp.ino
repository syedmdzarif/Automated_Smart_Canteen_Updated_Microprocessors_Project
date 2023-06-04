#include <WiFi.h>
#include <HTTPClient.h>

const char ssid[] = "Net";
const char password[] = "123123123";

String HOST_NAME = "http://192.168.43.208"; // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME   = "/connect_chrome.php";  //REPLACE WITH YOUR PHP FILE NAME
String tempQuery = "?order_id=234&student_id=89&items=mbdfb&table_no=4&bill=441";

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;
  String server = HOST_NAME + PHP_FILE_NAME + tempQuery;
  http.begin(server); 
  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("HTTP GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {

}
