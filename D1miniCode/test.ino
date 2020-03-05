#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

char* ssid = "UPC9472151";
char* password =  "zv5pbYVnrrf5";


void setup() {

  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {

// if(WiFi.status() == WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;

   http.begin("http://192.168.0.66:4000/");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header
   char buffer[20];
    sprintf(buffer, "{\"song\":\"%d\"}", rand() % (60 + 1 - 0) + 0);
   int httpResponseCode = http.POST(buffer);   //Send the actual POST request

   if(httpResponseCode>0){

    String response = http.getString();                       //Get the response to the request

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer

   }else{

    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);

   }

   http.end();  //Free resources

//  }else{

//     Serial.println("Error in WiFi connection");

//  }

  delay(2500);  //Send a request every 10 seconds

}