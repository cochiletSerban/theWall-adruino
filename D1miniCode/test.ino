#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "SPISlave.h"

char* ssid = "UPC9472151";
char* password =  "zv5pbYVnrrf5";
uint8_t songId = NULL;

void setup() {
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  SPISlave.onData([](uint8_t * data, size_t len) {
    Serial.printf("songId: %d\n", data[0]);
    songId = data[0];
  });

  SPISlave.begin();
}

void loop() {

  if (songId) {
    HTTPClient http;
    http.begin("http://192.168.0.66:4000/");
    http.addHeader("Content-Type", "application/json");

    char buffer[20];
    if (songId == 61) songId = 0;
    sprintf(buffer, "{\"song\":\"%d\"}", songId);

    int httpResponseCode = http.POST(buffer);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
    songId = NULL;
  }

}